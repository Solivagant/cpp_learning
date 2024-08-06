//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_BASICENEMY_H
#define CPP_LEARNING_BASICENEMY_H

#include "AEntity.h"
#include "Player.h"

class EntityResolver;


class BasicEnemy : public AEntity {
public:
    static const int Radius = 15;
    constexpr static const float InitialSpeed = 120.0f;
    static const int AvoidanceBonus = 3;

    BasicEnemy(Vector2 initialPosition);
    void Draw(float deltaTime);
    void Move(float deltaTime, Player* player, std::vector<BasicEnemy*> enemies);
    void MarkDying();
    void MarkForDeletion();
    bool GetToDelete() { return toDelete; }
private:
    bool toDelete;
    bool isDying;
    float ColorAlpha = 1;
    float timeDying = 0;
};

#endif //CPP_LEARNING_BASICENEMY_H
