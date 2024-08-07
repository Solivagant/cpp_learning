//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_GAMELOOP_H
#define CPP_LEARNING_GAMELOOP_H

#include "../../lib/raylib.h"
#include "../../lib/raymath.h"
#include "../Entities/EntityResolver.h"
#include "Background.h"
#include <thread>
#include <chrono>

class GameLoop {
public:
    int RunGame(int screenWidth, int screenHeight);

private:
    EntityResolver* entityResolver;
    Background* background;
    int screenWidth;
    int screenHeight;
    void DrawEnemies(float deltaTime);
    void MoveEnemies(float deltaTime);
    void RegisterPlayer();
    void FreeMemory();
    bool ProcessCombat(float deltaTime);
};

void SpawnGenerateEnemies(EntityResolver* entityResolver);
void SpawnRespawn(Player* player);

#endif //CPP_LEARNING_GAMELOOP_H
