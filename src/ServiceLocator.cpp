//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "ServiceLocator.h"

void ServiceLocator::Init() {
    //make_unique creates an instance and wraps it in a pointer
    //make_shared
    //shared_ptr provide limited garbage collection facility
    //it owns the pointer and shares that ownership
    mutex = std::make_shared<std::mutex>();

    gameData = new GameData(1024,760);
    playerData = new PlayerData();
    entityResolver = new EntityResolver();

    combatHandler = new CombatHandler(mutex, gameData, playerData, entityResolver);
    waveSystem = new WaveSystem(mutex, playerData, gameData, entityResolver);
    backgroundService = new BackgroundService();
}

GameData *ServiceLocator::GetGameData() const {
    return gameData;
}

WaveSystem *ServiceLocator::GetWaveSystem() const {
    return waveSystem;
}

CombatHandler *ServiceLocator::GetCombatHandler() const {
    return combatHandler;
}

EntityResolver *ServiceLocator::GetEntityResolver() const {
    return entityResolver;
}

BackgroundService *ServiceLocator::GetBackgroundService() const {
    return backgroundService;
}

PlayerData *ServiceLocator::GetPlayerData() const {
    return playerData;
}

