//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_WAVESYSTEM_H
#define CPP_LEARNING_WAVESYSTEM_H

#include "../Entities/EntityResolver.h"
#include "../Game/GameData.h"
#include <map>
#include <random>
#include <algorithm>

class WaveSystem {
public:
    WaveSystem(std::shared_ptr<std::mutex> &mutex, PlayerData* playerData, GameData* gameData,
               EntityResolver* entityResolver);
    void StartWave();
    void Shutdown();
    void SpawnGenerateEnemies();
    void GenerateEnemies(int count);
    void BlowUpEnemies();
    void CreateBasicEnemyA(Vector2 position);
    void CreateBasicEnemyB(Vector2 position);

private:
    constexpr static const float deviation = 20.0f;
    constexpr static const int spawnSleepMs = 2000;
    constexpr static const int spawnIntervalMs = 5000;

    std::map<int, int> levelToEnemyCount {{1, 15},
                                          {2, 20},
                                          {3, 30},
                                          {4, 40},
                                          {5, 45},
                                          {6, 50},
                                          {7, 55},
                                          {8, 60},
                                          {9, 65},
                                          {10, 65},
                                          {11, 65},
                                          {12, 65},
                                          {13, 70},
                                          {14, 75},
                                          {15, 80},
                                          {16, 80},
                                          {17, 80},
                                          {18, 90},
                                          {19, 100},
                                          {20, 135}

    };

    EntityResolver* entityResolver;
    GameData* gameData;
    PlayerData* playerData;
    std::thread tWave;
    std::thread tBlowUp;
    std::shared_ptr<std::mutex> mutex;
    std::random_device rd;
    std::mt19937 e{rd()};

    void SpawnBlowUpEnemies();

    int GetEnemyCountForLevel(int level);
};
#endif //CPP_LEARNING_WAVESYSTEM_H
