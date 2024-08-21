//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_GAMELOOP_H
#define CPP_LEARNING_GAMELOOP_H

#include "../../lib/raylib.h"
#include "../../lib/raymath.h"
#include "../Entities/EntityResolver.h"
#include "BackgroundService.h"
#include "ServiceLocator.h"
#include <thread>
#include <chrono>

class GameLoop {
public:
    int RunGame(ServiceLocator* serviceLocator);

private:
    GameData* gameData;
    WaveSystem* waveSystem;
    CombatHandler* combatHandler;
    EntityResolver* entityResolver;

    BackgroundService* background;
    PlayerData* playerData;
    Player *player;

    void DrawEnemies(float deltaTime);
    void MoveEnemies(float deltaTime);
    Player* RegisterPlayer();
    void FreeMemory();

    void SpawnRespawn();
};

#endif //CPP_LEARNING_GAMELOOP_H
