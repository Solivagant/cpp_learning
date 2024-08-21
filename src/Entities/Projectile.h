//
// Created by Geraldo Nascimento on 06/08/2024.
//

#ifndef CPP_LEARNING_PROJECTILE_H
#define CPP_LEARNING_PROJECTILE_H

#include "../../lib/raylib.h"
#include "../../lib/raymath.h"

class Projectile {
public:
    static const int Radius = 12;

    constexpr static const float InitialSpeed = 420.0f;
    constexpr static const float TimeToLive = 1.0f;

    void Init(Vector2 initialPosition, Vector2 targetPosition);
    void Draw() ;
    void Move(float d);
    void MarkForDeletion();
    bool GetToDelete() { return toDelete; }

    Vector2 GetPosition() {
        return position;
    }

private:
    Vector2 targetDirection;
    float timeAlive;
    bool toDelete;

    Vector2 position;
    float speed;
};

#endif //CPP_LEARNING_PROJECTILE_H
