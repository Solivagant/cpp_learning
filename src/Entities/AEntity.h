//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_AENTITY_H
#define CPP_LEARNING_AENTITY_H

#include "../../lib/raylib.h"

class AEntity {
public:
    virtual void Draw() = 0;
    virtual void Move(float deltaTime) = 0;

    Vector2 GetPosition() {
        return position;
    }

protected:
    Vector2 position;
    float speed;
};

#endif //CPP_LEARNING_AENTITY_H
