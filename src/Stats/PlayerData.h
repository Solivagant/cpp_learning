//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_PLAYERDATA_H
#define CPP_LEARNING_PLAYERDATA_H

#include "rxcpp/rx.hpp"
#include "../../lib/raylib.h"

class PlayerData {
private:
public:
    int GetHealth() const;
    void SetHealth(int health);
    void UpdatePosition(Vector2 position);

private:
    int maxHealth = 10;
    int health = 10;

    int xpPerLevel = 10;
    int xp = 0;

    int level = 1;
    rxcpp::subjects::subject<Vector2> position;
    rxcpp::subscriber<Vector2> positionSubscriber = position.get_subscriber();
    rxcpp::observable<Vector2> observable = position.get_observable();

public:
    rxcpp::observable<Vector2>* GetPositionObservable();
    int GetXPToNextLevel();
    int GetXP() const;
    void SetXP(int xp);
    int GetLevel();
public:
    bool IsDead();
    float GetMaxHealth();
};
#endif //CPP_LEARNING_PLAYERDATA_H
