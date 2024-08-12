//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "WaveSystem.h"

//TODO move the threads to be class functions
WaveSystem::WaveSystem(std::shared_ptr<std::mutex> &vectorMutex, PlayerData* playerData, GameData* gameData,
                       EntityResolver* entityResolver) {
    this->entityResolver = entityResolver;
    this->gameData = gameData;
    this->playerData = playerData;
    this->vectorMutex = vectorMutex;
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
            //TODO the generate should be in this class
            entityResolver->GenerateEnemies(10 * playerData->GetLevel());
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
