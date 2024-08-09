//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "PlayerData.h"

bool PlayerData::IsDead() {
    return health <= 0;
}

int PlayerData::GetHealth() const {
    return health;
}

void PlayerData::SetHealth(int health) {
    this->health = health;
}

float PlayerData::GetMaxHealth() {
    return maxHealth;
}

int PlayerData::GetXP() const {
    return xp;
}

void PlayerData::SetXP(int xp) {
    PlayerData::xp = xp;
}

int PlayerData::GetXPToNextLevel() {
    return xpPerLevel;
}
