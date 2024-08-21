//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_BASICENEMY_H
#define CPP_LEARNING_BASICENEMY_H

#include "Player.h"
#include "../../lib/raymath.h"
#include <sstream>
#include <map>

static int counter;

class BasicEnemy  {
public:
    BasicEnemy();

    void Init(Vector2 initialPosition, int health, int radius, int initialSpeed, std::map<int, int> levelToSpeed, Color color);

    void Draw(float deltaTime) ;
    void Move(int playerLevel, float deltaTime, Player* player, std::vector<std::shared_ptr<BasicEnemy>> enemies) ;
    void MarkDying(bool isBlowingUp) ;
    void MarkForDeletion();

    bool GetToDelete()  { return toDelete; }

    bool GetIsDying()  { return isDying; }

    void DealDamage(int amount) ;

    void KillFromHittingPlayer() ;
    int GetRadius() ;
    virtual float GetInitialSpeed();
    Vector2 GetPosition() ;
    int GetId();

private:
    int id;

    int health;
    int maxHealth;
    int radius;
    int initialSpeed;
    Color color;

    Vector2 position;
    bool toDelete;
    bool isDying;
    bool isBlowingUp;
    float colorAlpha = 1;
    float timeDying = 0;
    float GetSpeedByPlayerLevel(int level);

    std::map<int, int> levelToSpeed;
};

bool CompareByDistance(std::shared_ptr<BasicEnemy> a, std::shared_ptr<BasicEnemy> b, const Vector2 &point);

#endif //CPP_LEARNING_BASICENEMY_H
