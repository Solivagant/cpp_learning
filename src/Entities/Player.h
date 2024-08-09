//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_PLAYER_H
#define CPP_LEARNING_PLAYER_H

#include "../../lib/raylib.h"
#include "AEntity.h"
#include "../Stats/PlayerData.h"
#include "../Game/GameData.h"
#include <thread>
#include <chrono>

// Inheritance is private by default, so specify public
class Player : public AEntity {
public:
    static const int Radius = 15;
    constexpr static const float InitialSpeed = 200.0f;

    Player(PlayerData* playerData, GameData* gameData, Vector2 initialPosition);
    void Move(float deltaTime);
    void Draw();
    bool Fire(float deltaTime);
    void Respawn();
    void DealDamage(int amount) override;
private:
    PlayerData* playerData;
    Vector2 initialPosition;
    float timeMoveHeld;
    float timeToFire;
    bool IsInputRightHeld() const;
    bool IsInputLeftHeld() const;
    bool IsInputUpHeld() const;
    bool IsInputDownHeld() const;
    GameData* gameData;
    Texture texture;
};

#endif //CPP_LEARNING_PLAYER_H
