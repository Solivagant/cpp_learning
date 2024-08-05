//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_BASICENEMY_H
#define CPP_LEARNING_BASICENEMY_H

#include "AEntity.h"
#include "EntityResolver.h"

class BasicEnemy : public AEntity {
public:
    BasicEnemy(EntityResolver* resolver, Vector2 initialPosition);
    void Draw() override;
    void Move(float deltaTime) override;
private:
    EntityResolver *entityResolver;
};

#endif //CPP_LEARNING_BASICENEMY_H
