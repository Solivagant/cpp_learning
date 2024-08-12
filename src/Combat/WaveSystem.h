//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_WAVESYSTEM_H
#define CPP_LEARNING_WAVESYSTEM_H

#include "../Entities/EntityResolver.h"
#include "../Game/GameData.h"

class WaveSystem {
public:
    WaveSystem(std::shared_ptr<std::mutex> &mutex, PlayerData* playerData, GameData* gameData,
               EntityResolver* entityResolver);
    void StartWave();
    void Shutdown();
    void SpawnGenerateEnemies();
    void GenerateEnemies(int count);
    void BlowUpEnemies();

private:
    constexpr static const float deviation = 20.0f;
    constexpr static const int spawnSleepMs = 500;
    constexpr static const int spawnIntervalMs = 5000;
    constexpr static const int enemyCountPerLevel = 10;

    EntityResolver* entityResolver;
    GameData* gameData;
    PlayerData* playerData;
    std::thread tWave;
    std::thread tBlowUp;
    std::shared_ptr<std::mutex> mutex;
    std::random_device rd;
    std::mt19937 e{rd()};
    Vector2 playerPos;

    void SpawnBlowUpEnemies();

};
#endif //CPP_LEARNING_WAVESYSTEM_H
