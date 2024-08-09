//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_PLAYERDATA_H
#define CPP_LEARNING_PLAYERDATA_H

class PlayerData {
private:
public:
    int GetHealth() const;
    void SetHealth(int health);
private:
    int maxHealth = 10;
    int health = 10;
public:
    bool IsDead();
    float GetMaxHealth();
};

#endif //CPP_LEARNING_PLAYERDATA_H
