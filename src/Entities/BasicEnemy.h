//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_BASICENEMY_H
#define CPP_LEARNING_BASICENEMY_H

#include "AEntity.h"
#include "Player.h"

class EntityResolver;

static const int BodySize = 15;
static const int AvoidanceRange = 30;

class BasicEnemy : public AEntity {
public:
    BasicEnemy(Vector2 initialPosition);
    void Draw() override;
    void Move(float deltaTime, Player* player, std::vector<BasicEnemy*> enemies);
};

#endif //CPP_LEARNING_BASICENEMY_H
