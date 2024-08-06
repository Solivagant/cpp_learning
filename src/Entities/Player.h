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
    static const int Radius = 25;
    constexpr static const float InitialSpeed = 200.0f;


    Player(Vector2 initialPosition);
    void Move(float deltaTime);
    void Draw() ;
    bool Fire(float deltaTime);
    Vector2 GetFirePosition();
private:
    float timeMoveHeld;
    float timeToFire;
};

#endif //CPP_LEARNING_PLAYER_H
