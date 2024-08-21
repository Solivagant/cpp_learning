//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "WaveSystem.h"

WaveSystem::WaveSystem(std::shared_ptr<std::mutex> &mutex, PlayerData* playerData, GameData* gameData,
                       EntityResolver* entityResolver) {
    this->entityResolver = entityResolver;
    this->gameData = gameData;
    this->playerData = playerData;
    this->mutex = mutex;
}

void WaveSystem::StartWave() {
    tWave = std::thread(&WaveSystem::SpawnGenerateEnemies, this);
}

void WaveSystem::Shutdown() {
    tWave.join();
}

void WaveSystem::BlowUpEnemies() {
    tBlowUp = std::thread(&WaveSystem::SpawnBlowUpEnemies, this);
    tBlowUp.join();
}

void WaveSystem::SpawnBlowUpEnemies() {
    auto enemies = entityResolver->GetEnemies();

    Vector2 playerPos = playerData->GetPosition();

    //Sort enemies by position closest to player
    std::sort(enemies.begin(), enemies.end(), [&](std::shared_ptr<BasicEnemy> a, std::shared_ptr<BasicEnemy> b) {
        return CompareByDistance(a, b, playerPos);
    });

    for (auto enemy: enemies) {
        enemy->MarkDying(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(std::clamp((int)(enemies.size() / 10), 1, 3)));
    }

    entityResolver->DeleteEnemies();
}

void WaveSystem::SpawnGenerateEnemies() {
    int timePassed = 0;

    std::this_thread::sleep_for(std::chrono::milliseconds(spawnSleepMs));
    while (gameData->GetIsRunning()) {
        std::unique_lock<std::mutex> lock(*mutex);

        if (!playerData->IsDead()) {
            GenerateEnemies(GetEnemyCountForLevel(playerData->GetLevel()));
            timePassed = 0;
        }

        if (playerData->IsDead()) {
            timePassed = spawnIntervalMs;
        }

        lock.unlock();

        while (!playerData->IsDead() && timePassed < spawnIntervalMs && gameData->GetIsRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(spawnSleepMs));
            timePassed += spawnSleepMs;
        }
    }
}

void WaveSystem::GenerateEnemies(int count) {
    Vector2 playerPos = playerData->GetPosition();

    int up = 0 - deviation * 2;
    int down =  gameData->GetScreenHeight() + deviation * 2;
    int left =  0 - deviation * 2;
    int right = gameData->GetScreenWidth() + deviation * 2;

    if(gameData->GetCameraFollowsPlayer())
    {
         up = playerPos.y - gameData->GetScreenHeight() / 2 - deviation * 2;
         down = playerPos.y + gameData->GetScreenHeight() / 2 + deviation * 2;
         left = playerPos.x - gameData->GetScreenWidth() / 2 - deviation * 2;
         right = playerPos.x + gameData->GetScreenWidth() / 2 + deviation * 2;
    }

    auto upDist = std::uniform_int_distribution<int>(up - deviation, up);
    auto downDist = std::uniform_int_distribution<int>(down, down + deviation);
    auto leftRightDist = std::uniform_int_distribution<int>(left, right);

    auto leftDist = std::uniform_int_distribution<int>(left - deviation, left);
    auto rightDist = std::uniform_int_distribution<int>(right, right + deviation);
    auto upDownDist = std::uniform_int_distribution<int>(up, down);

    for (int i = 0; i < count; ++i) {
        //Random position up the screen
        Vector2 randomPosAbove{float(leftRightDist(e)), float(upDist(e))};
        CreateBasicEnemyA(randomPosAbove);

        //Random position down the screen
        Vector2 randomPosBelow{float(leftRightDist(e)), float(downDist(e))};
        CreateBasicEnemyA(randomPosBelow);

        //Random position to the left of the screen
        Vector2 randomPosLeft{float(leftDist(e)), float(upDownDist(e))};
        CreateBasicEnemyA(randomPosLeft);

        //Random position to the right of the screen
        Vector2 randomPosRight{float(rightDist(e)), float(upDownDist(e))};
        CreateBasicEnemyA(randomPosRight);
    }

    for (int i = 0; i < count / 10; ++i) {
        Vector2 randomPosAbove{float(leftRightDist(e)), float(upDist(e))};
        CreateBasicEnemyB(randomPosAbove);

        Vector2 randomPosBelow{float(leftRightDist(e)), float(downDist(e))};
        CreateBasicEnemyB(randomPosBelow);

        Vector2 randomPosLeft{float(leftDist(e)), float(upDownDist(e))};
        CreateBasicEnemyB(randomPosLeft);

        Vector2 randomPosRight{float(rightDist(e)), float(upDownDist(e))};
        CreateBasicEnemyB(randomPosRight);
    }
}

int WaveSystem::GetEnemyCountForLevel(int level) {
    if(levelToEnemyCount.contains(level)) return levelToEnemyCount[level];

    return levelToEnemyCount[levelToEnemyCount.size()-1];
}

//Config map so things can be tweaked without relying on a formula
void WaveSystem::CreateBasicEnemyA(Vector2 position) {
    std::map<int, int> levelToSpeed{{1,  5},
                                    {2,  10},
                                    {3,  15},
                                    {4,  20},
                                    {5,  25},
                                    {6,  30},
                                    {7,  35},
                                    {8,  40},
                                    {9,  50},
                                    {10, 60},
                                    {11, 70},
                                    {12, 80},
                                    {13, 90},
                                    {14, 100},
                                    {15, 110},
                                    {16, 120},
                                    {17, 130},
                                    {18, 135},
                                    {19, 140},
                                    {20, 150},
    };
    std::shared_ptr<BasicEnemy> basicEnemy = entityResolver->AcquireEnemy();
    basicEnemy->Init(position, 2, 15, 80,levelToSpeed, RED);
}

void WaveSystem::CreateBasicEnemyB(Vector2 position) {

    std::map<int, int> levelToSpeed{{1,  60},
                                    {2,  70},
                                    {3,  80},
                                    {4,  90},
                                    {5,  100},
                                    {6,  110},
                                    {7,  120},
                                    {8,  130},
                                    {9,  140},
                                    {10, 150}};

    std::shared_ptr<BasicEnemy> basicEnemy = entityResolver->AcquireEnemy();
    basicEnemy->Init(position, 1, 10, 90,levelToSpeed, SKYBLUE);
}
