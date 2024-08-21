//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_PLAYER_H
#define CPP_LEARNING_PLAYER_H

#include "../../lib/raylib.h"
#include "../Stats/PlayerData.h"
#include "../Game/GameData.h"
#include <thread>
#include <chrono>
#include <sstream>

class Player {
public:
    static const int Radius = 15;
    constexpr static const float InitialSpeed = 200.0f;

    Player(PlayerData* playerData, GameData* gameData, Vector2 initialPosition);
    void UpdateLevelStream();
    void Move(float deltaTime);
    void Draw();
    bool Fire(float deltaTime);
    void Respawn();
    void DealDamage(int amount);
    Vector2 GetPosition();
private:
    PlayerData* playerData;
    Vector2 initialPosition;
    Vector2 position;
    float speed;
    float timeMoveHeld;
    float timeToFire;
    int playerLevelCache;
    bool IsInputRightHeld() const;
    bool IsInputLeftHeld() const;
    bool IsInputUpHeld() const;
    bool IsInputDownHeld() const;
    GameData* gameData;
    void DrawUI();
    std::vector<char>*  levelString;
};

#endif //CPP_LEARNING_PLAYER_H
