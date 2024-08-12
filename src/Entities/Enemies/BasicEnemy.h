//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_BASICENEMY_H
#define CPP_LEARNING_BASICENEMY_H

#include "../AEntity.h"
#include "../Player.h"

class BasicEnemy : public AEntity {
public:
    static const int Radius = 15;
    constexpr static const float InitialSpeed = 120.0f;
    static const int AvoidanceBonus = 3;

    BasicEnemy(Vector2 initialPosition);
    void Draw(float deltaTime);
    void Move(int playerLevel, float deltaTime, Player* player, std::vector<BasicEnemy*> enemies);
    void MarkDying(bool isBlowingUp);
    void MarkForDeletion();
    bool GetToDelete() { return toDelete; }
    bool GetIsDying() { return isDying; }

    void DealDamage(int amount) override;

    void KillFromHittingPlayer();
private:
    int health = 3;
public:
    int GetHealth() const;
private:
    int maxHealth = 5;

    bool toDelete;
    bool isDying;
    float colorAlpha = 1;
    float timeDying = 0;
    bool isBlowingUp;
};

#endif //CPP_LEARNING_BASICENEMY_H
