//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "WaveSystem.h"
#include "../Util/MathUtil.h"
#include <algorithm>

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
    std::sort(enemies.begin(), enemies.end(), [&](AEntity* a, AEntity* b) {
        return CompareByDistance<AEntity>(a, b, playerPos);
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

    int up = playerPos.y - gameData->GetScreenHeight() / 2 - deviation * 2;
    int down = playerPos.y + gameData->GetScreenHeight() / 2 + deviation * 2;
    int left = playerPos.x - gameData->GetScreenWidth() / 2 - deviation * 2;
    int right = playerPos.x + gameData->GetScreenWidth() / 2 + deviation * 2;

    auto upDist = std::uniform_int_distribution<int>(up - deviation, up);
    auto downDist = std::uniform_int_distribution<int>(down, down + deviation);
    auto leftRightDist = std::uniform_int_distribution<int>(left, right);

    auto leftDist = std::uniform_int_distribution<int>(left - deviation, left);
    auto rightDist = std::uniform_int_distribution<int>(right, right + deviation);
    auto upDownDist = std::uniform_int_distribution<int>(up, down);

    for (int i = 0; i < count; ++i) {
        //Random position up the screen
        Vector2 randomPosAbove{float(leftRightDist(e)), float(upDist(e))};
        auto* basicEnemy = new EnemyA(randomPosAbove);
        entityResolver->RegisterEnemy(basicEnemy);

        //Random position down the screen
        Vector2 randomPosBelow{float(leftRightDist(e)), float(downDist(e))};
        basicEnemy = new EnemyA(randomPosBelow);
        entityResolver->RegisterEnemy(basicEnemy);

        //Random position to the left of the screen
        Vector2 randomPosLeft{float(leftDist(e)), float(upDownDist(e))};
        basicEnemy = new EnemyA(randomPosLeft);
        entityResolver->RegisterEnemy(basicEnemy);

        //Random position to the right of the screen
        Vector2 randomPosRight{float(rightDist(e)), float(upDownDist(e))};
        basicEnemy = new EnemyA(randomPosRight);
        entityResolver->RegisterEnemy(basicEnemy);
    }
}

int WaveSystem::GetEnemyCountForLevel(int level) {
    if(levelToEnemyCount.contains(level)) return levelToEnemyCount[level];

    return levelToEnemyCount[levelToEnemyCount.size()-1];
}

