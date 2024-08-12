//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_ENEMYA_H
#define CPP_LEARNING_ENEMYA_H

#include "../AEntity.h"
#include "../Player.h"

class EnemyA : public AEntity {
public:
    static const int Radius = 15;
    constexpr static const float InitialSpeed = 80.0f;
    static const int AvoidanceBonus = 3;

    EnemyA(Vector2 initialPosition);
    void Draw(float deltaTime);
    void Move(int playerLevel, float deltaTime, Player* player, std::vector<EnemyA*> enemies);
    void MarkDying(bool isBlowingUp);
    void MarkForDeletion();
    bool GetToDelete() { return toDelete; }
    bool GetIsDying() { return isDying; }

    void DealDamage(int amount) override;

    void KillFromHittingPlayer();
private:
    int health = 2;
public:
    int GetHealth() const;
private:
    int maxHealth = 2;

    bool toDelete;
    bool isDying;
    float colorAlpha = 1;
    float timeDying = 0;
    bool isBlowingUp;
};

#endif //CPP_LEARNING_ENEMYA_H
