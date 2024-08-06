//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_GAMELOOP_H
#define CPP_LEARNING_GAMELOOP_H

#include "../../lib/raylib.h"
#include "../../lib/raymath.h"
#include "../Entities/EntityResolver.h"

class GameLoop {
public:
    int RunGame(int screenWidth, int screenHeight);

private:
    EntityResolver* entityResolver;
    int screenWidth;
    int screenHeight;
    void DrawEnemies();
    void MoveEnemies(float d);
    void GenerateEnemies(int i);
    void RegisterPlayer();
    void FreeMemory();
};

#endif //CPP_LEARNING_GAMELOOP_H
