//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "WaveSystem.h"

void SpawnGenerateEnemies(PlayerData* playerData, GameData *gameData, EntityResolver *entityResolver);

WaveSystem::WaveSystem(PlayerData* playerData, GameData *gameData, EntityResolver *entityResolver) {
    this->entityResolver = entityResolver;
    this->gameData = gameData;
    this->playerData = playerData;
    keepRunning = new bool(true);
}

void WaveSystem::StartWave() {
    t1 = std::thread(SpawnGenerateEnemies, playerData, gameData, entityResolver);
}

void WaveSystem::Shutdown() {
    t1.join();
}

void SpawnGenerateEnemies(PlayerData* playerData, GameData *gameData, EntityResolver *entityResolver) {
    int timePassed = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    while (gameData->GetIsRunning()) {
        if(!playerData->IsDead()){
            entityResolver->GenerateEnemies(10);
            timePassed = 0;
        }

        while (!playerData->IsDead() && timePassed < 5000 && gameData->GetIsRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            timePassed += 500;
        }
    }

}