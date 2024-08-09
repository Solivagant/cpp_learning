//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_PLAYER_H
#define CPP_LEARNING_PLAYER_H

#include "../../lib/raylib.h"
#include "AEntity.h"
#include "../Stats/PlayerData.h"
#include <thread>
#include <chrono>

// Inheritance is private by default, so specify public
class Player : public AEntity {
public:
    static const int Radius = 15;
    constexpr static const float InitialSpeed = 200.0f;

    Player(PlayerData* playerData, Vector2 initialPosition);
    void Move(float deltaTime);
    void Draw() ;
    bool Fire(float deltaTime);
    Vector2 GetFirePosition();
    void Respawn();
    void DealDamage(int amount) override;
private:
    PlayerData* playerData;
    Vector2 initialPosition;
    float timeMoveHeld;
    float timeToFire;
};


#endif //CPP_LEARNING_PLAYER_H
