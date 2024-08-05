//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_PLAYER_H
#define CPP_LEARNING_PLAYER_H

#include "../../lib/raylib.h"

class Player {
public:
    Player(Vector2 initialPosition);
    void DoMovement(float deltaTime);
    void DoDraw();
private:
    Vector2 playerPosition;
    float playerSpeed;
};

#endif //CPP_LEARNING_PLAYER_H
