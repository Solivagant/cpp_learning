//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_PLAYERDATA_H
#define CPP_LEARNING_PLAYERDATA_H

#include "../../lib/raylib.h"

class PlayerData {
private:
public:
    int GetHealth() const;
    void SetHealth(int health);
    void UpdatePosition(Vector2 position);
    Vector2 GetPosition();

private:
    int maxHealth = 10;
    int health = 10;

    int xpPerLevel = 10;
    int xp = 0;

    int level = 1;

    Vector2 position;

public:
    int GetXPToNextLevel();
    int GetXP() const;
    void SetXP(int xp);
    int GetLevel();
public:
    bool IsDead();
    float GetMaxHealth();
};
#endif //CPP_LEARNING_PLAYERDATA_H
