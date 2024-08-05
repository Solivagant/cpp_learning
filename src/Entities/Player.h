//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_PLAYER_H
#define CPP_LEARNING_PLAYER_H

#include "../../lib/raylib.h"
#include "AEntity.h"

// Inheritance is private here by default, so specify public
class Player : public AEntity {
public:
    Player(Vector2 initialPosition);
    void Move(float deltaTime) override;
    void Draw() override;
};

#endif //CPP_LEARNING_PLAYER_H
