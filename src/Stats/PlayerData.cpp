//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "PlayerData.h"

void PlayerData::UpdatePosition(Vector2 position)
{
    this->position = position;
}

bool PlayerData::IsDead() {
    return health <= 0;
}

int PlayerData::GetHealth() const {
    return health;
}

void PlayerData::SetHealth(int health) {
    this->health = health;
    if (IsDead()) {
        SetXP(0);
        level = 1;
    }
}

float PlayerData::GetMaxHealth() {
    return maxHealth;
}

int PlayerData::GetXP() const {
    return xp;
}

void PlayerData::SetXP(int xp) {
    this->xp = xp;
    if (xp >= GetXPToNextLevel()) {
        this->xp = 0;
        level++;
    }
}

int PlayerData::GetXPToNextLevel() {
    return xpPerLevel + level * 20 + level * 3;
}

int PlayerData::GetLevel() {
    return level;
}

Vector2 PlayerData::GetPosition() {
    return position;
}
