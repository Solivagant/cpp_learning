//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_PLAYER_H
#define CPP_LEARNING_PLAYER_H

#include "../../lib/raylib.h"
#include "AEntity.h"
#include <thread>
#include <chrono>

// Inheritance is private by default, so specify public
class Player : public AEntity {
public:
    static const int Radius = 15;
    constexpr static const float InitialSpeed = 200.0f;

    Player(Vector2 initialPosition);
    void Move(float deltaTime);
    void Draw() ;
    bool Fire(float deltaTime);
    Vector2 GetFirePosition();
    bool IsDead();
    void Kill();
    void Respawn();
private:
    Vector2 initialPosition;
    bool isDead;
    float timeMoveHeld;
    float timeToFire;
};


#endif //CPP_LEARNING_PLAYER_H
