//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "WaveSystem.h"

static const float Deviation = 20.0f;

WaveSystem::WaveSystem(std::shared_ptr<std::mutex> &vectorMutex, PlayerData* playerData, GameData* gameData,
                       EntityResolver* entityResolver) {
    this->entityResolver = entityResolver;
    this->gameData = gameData;
    this->playerData = playerData;
    this->vectorMutex = vectorMutex;

    const rxcpp::observable<Vector2> observable = *playerData->GetPositionObservable();
    observable.subscribe(
            [this](Vector2 playerPos) {
                this->playerPos = playerPos;
            });
}

void WaveSystem::StartWave() {
    t1 = std::thread(&WaveSystem::SpawnGenerateEnemies, this);
}

void WaveSystem::Shutdown() {
    t1.join();
}

void WaveSystem::SpawnGenerateEnemies() {
    int timePassed = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    while (gameData->GetIsRunning()) {
        std::unique_lock<std::mutex> lock(*vectorMutex);

        if (!playerData->IsDead()) {
            GenerateEnemies(10 * playerData->GetLevel());
            timePassed = 0;
        }

        if (playerData->IsDead()) {
            timePassed = 5000;
        }

        lock.unlock();

        while (!playerData->IsDead() && timePassed < 5000 && gameData->GetIsRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            timePassed += 500;
        }
    }
}

void WaveSystem::GenerateEnemies(int count) {

    int up = playerPos.y - gameData->GetScreenHeight() / 2 - Deviation * 2;
    int down = playerPos.y + gameData->GetScreenHeight() / 2 + Deviation * 2;
    int left = playerPos.x - gameData->GetScreenWidth() / 2 - Deviation * 2;
    int right = playerPos.x + gameData->GetScreenWidth() / 2 + Deviation * 2;

    auto upDist = std::uniform_int_distribution<int>(up - Deviation, up);
    auto downDist = std::uniform_int_distribution<int>(down, down + Deviation);
    auto leftRightDist = std::uniform_int_distribution<int>(left, right);

    auto leftDist = std::uniform_int_distribution<int>(left - Deviation, left);
    auto rightDist = std::uniform_int_distribution<int>(right, right + Deviation);
    auto upDownDist = std::uniform_int_distribution<int>(up, down);

    for (int i = 0; i < count; ++i) {
        //Random position up the screen
        Vector2 randomPosAbove{float(leftRightDist(e)), float(upDist(e))};
        auto* basicEnemy = new BasicEnemy(randomPosAbove);
        entityResolver->RegisterEnemy(basicEnemy);

        //Random position down the screen
        Vector2 randomPosBelow{float(leftRightDist(e)), float(downDist(e))};
        basicEnemy = new BasicEnemy(randomPosBelow);
        entityResolver->RegisterEnemy(basicEnemy);

        //Random position to the left of the screen
        Vector2 randomPosLeft{float(leftDist(e)), float(upDownDist(e))};
        basicEnemy = new BasicEnemy(randomPosLeft);
        entityResolver->RegisterEnemy(basicEnemy);

        //Random position to the right of the screen
        Vector2 randomPosRight{float(rightDist(e)), float(upDownDist(e))};
        basicEnemy = new BasicEnemy(randomPosRight);
        entityResolver->RegisterEnemy(basicEnemy);

    }
}

