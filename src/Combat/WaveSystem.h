//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_WAVESYSTEM_H
#define CPP_LEARNING_WAVESYSTEM_H

#include "../Entities/EntityResolver.h"
#include "../Game/GameData.h"

class WaveSystem {
public:
    WaveSystem(PlayerData* playerData, GameData *gameData, EntityResolver *entityResolver);
    void StartWave();
    void Shutdown();
private:
    EntityResolver *entityResolver;
    GameData *gameData;
    PlayerData * playerData;
    std::thread t1;
    bool* keepRunning;
};

#endif //CPP_LEARNING_WAVESYSTEM_H
