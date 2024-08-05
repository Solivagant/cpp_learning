//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_GAMELOOP_H
#define CPP_LEARNING_GAMELOOP_H

#include "../../lib/raylib.h"
#include "../../lib/raymath.h"

class GameLoop {
public:
    int RunGame(int screenWidth, int screenHeight);

private:
    int screenWidth;
    int screenHeight;
};

#endif //CPP_LEARNING_GAMELOOP_H
