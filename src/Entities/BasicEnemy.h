//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_BASICENEMY_H
#define CPP_LEARNING_BASICENEMY_H

#include "IEntity.h"
#include "EntityResolver.h"

class BasicEnemy : IEntity {
public:
    BasicEnemy(EntityResolver* resolver, Vector2 initialPosition);
    void Draw() override;
    void Move(float deltaTime) override;
};

#endif //CPP_LEARNING_BASICENEMY_H
