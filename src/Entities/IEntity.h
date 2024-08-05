//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_IENTITY_H
#define CPP_LEARNING_IENTITY_H

#include "../../lib/raylib.h"

class IEntity {
public:
    virtual void Draw() = 0;
    virtual void Move(float deltaTime) = 0;
protected:
    Vector2 position;
    float speed;
};

#endif //CPP_LEARNING_IENTITY_H
