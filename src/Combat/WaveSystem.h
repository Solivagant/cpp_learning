//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_WAVESYSTEM_H
#define CPP_LEARNING_WAVESYSTEM_H

#include "../Entities/EntityResolver.h"
#include "../Game/GameData.h"

class WaveSystem {
public:
    WaveSystem(std::shared_ptr<std::mutex> &vectorMutex, PlayerData* playerData, GameData* gameData,
               EntityResolver* entityResolver);
    void StartWave();
    void Shutdown();
    void SpawnGenerateEnemies();

private:
    EntityResolver* entityResolver;
    GameData* gameData;
    PlayerData* playerData;
    std::thread t1;
    std::shared_ptr<std::mutex> vectorMutex;
};
#endif //CPP_LEARNING_WAVESYSTEM_H
