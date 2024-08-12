//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_SERVICELOCATOR_H
#define CPP_LEARNING_SERVICELOCATOR_H

#include "Combat/CombatHandler.h"
#include "Combat/WaveSystem.h"
#include "Game/GameData.h"
#include "Game/BackgroundService.h"
#include <map>
#include <thread>
#include <mutex>


class ServiceLocator {
public:
    void Init();
    GameData *GetGameData() const;
    WaveSystem *GetWaveSystem() const;
    CombatHandler *GetCombatHandler() const;
    EntityResolver *GetEntityResolver() const;
    PlayerData *GetPlayerData() const;
    BackgroundService *GetBackgroundService() const;
private:
    GameData* gameData;
    WaveSystem* waveSystem;
    BackgroundService* backgroundService;
    CombatHandler* combatHandler;
    EntityResolver* entityResolver;
    PlayerData* playerData;
    std::shared_ptr<std::mutex> vectorMutexPtr;
};

#endif //CPP_LEARNING_SERVICELOCATOR_H
