//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "BasicEnemy.h"
#include "../../lib/raymath.h"
#include <sstream>

BasicEnemy::BasicEnemy(){
    id = counter;
    counter++;
}

void BasicEnemy::Init(Vector2 initialPosition, int health, int radius, int initialSpeed,
                       std::map<int, int> levelToSpeed, Color color) {

    this->initialSpeed = initialSpeed;
    position = initialPosition;
    this->health = health;
    this->radius = radius;
    this->levelToSpeed = levelToSpeed;
    this->color = color;
    this->maxHealth = health;
    colorAlpha = 1;
    timeDying = 0;
    isDying = false;

    toDelete = false;
    isDying = false;
    isBlowingUp = false;
}

void BasicEnemy::Draw(float deltaTime) {
    if (isDying) {
        timeDying += deltaTime;

        if(isBlowingUp)
        {
            colorAlpha -= 2.5f * timeDying;
            DrawCircleV(position, radius, Fade(color, colorAlpha));
        }
        else
        {
            colorAlpha -= 10.5f * timeDying;
            DrawCircleV(position, radius, Fade(color, colorAlpha));
        }

        if (colorAlpha <= 0) {
            MarkForDeletion();
        }
    }
    else{
        DrawCircleV(position, radius, WHITE);
        DrawCircleV(position, radius, Fade(color, (float)health / maxHealth));
    }
}

// Moves towards the player
void BasicEnemy::Move(int playerLevel, float deltaTime, Player *player, std::vector<std::shared_ptr<BasicEnemy>> enemies) {
    Vector2 playerPosition = player->GetPosition();
    Vector2 directionToPlayer = Vector2Normalize(Vector2Subtract(playerPosition, position));

    position = Vector2Add(position, Vector2Scale(directionToPlayer, (GetInitialSpeed() + GetSpeedByPlayerLevel(playerLevel)) * deltaTime));

    for (std::shared_ptr<BasicEnemy> enemy: enemies) {
        if (enemy.get() == this) {
            continue;
        }

        Vector2 enemyPosition = enemy->GetPosition();
        if (Vector2Distance(enemyPosition, position) <= GetRadius() * 2 - 3) {
            Vector2 directionToEnemy = Vector2Normalize(Vector2Subtract(enemyPosition, position));
            position = Vector2Subtract(position, Vector2Scale(directionToEnemy, (GetInitialSpeed() + GetSpeedByPlayerLevel(playerLevel)) * deltaTime));
        }
    };
}

void BasicEnemy::MarkDying(bool isBlowingUp) {
    timeDying = 0;
    isDying = true;
    this->isBlowingUp = isBlowingUp;
//    MarkForDeletion();
}

void BasicEnemy::MarkForDeletion() {
    toDelete = true;
}

void BasicEnemy::DealDamage(int amount) {
    health = health - amount;
    if(health <= 0) {
        MarkDying(false);
    }
}

void BasicEnemy::KillFromHittingPlayer() {
    MarkDying(false);
}

int BasicEnemy::GetRadius() {
    return radius;
}

float BasicEnemy::GetInitialSpeed() {
    return initialSpeed;
}

Vector2 BasicEnemy::GetPosition() {
    return position;
}

float BasicEnemy::GetSpeedByPlayerLevel(int level) {
    if(levelToSpeed.contains(level)){
        return levelToSpeed[level];
    }
    else
    {
        return levelToSpeed[levelToSpeed.size()-1];
    }
}

bool CompareByDistance(std::shared_ptr<BasicEnemy> a, std::shared_ptr<BasicEnemy> b, const Vector2 &point) {
    float distanceA = Vector2Distance(a->GetPosition(), point);
    float distanceB = Vector2Distance(b->GetPosition(), point);
    return distanceA < distanceB;
}


int BasicEnemy::GetId() {
    return id;
}


