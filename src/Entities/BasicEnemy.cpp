//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include <iostream>
#include "BasicEnemy.h"
#include "../../lib/raymath.h"
#include "../../lib/raylib.h"

BasicEnemy::BasicEnemy(Vector2 initialPosition) {
    position = initialPosition;
    speed = InitialSpeed;
}

void BasicEnemy::Draw(float deltaTime) {

    if (isDying) {
        timeDying += deltaTime;
        ColorAlpha -= 1.5f * timeDying;

        if (ColorAlpha <= 0) {
            MarkForDeletion();
        }
    }
    DrawCircleV(position, Radius, Fade(RED, ColorAlpha));
}

// Moves towards the player
void BasicEnemy::Move(float deltaTime, Player *player, std::vector<BasicEnemy *> enemies) {
    Vector2 playerPosition = player->GetPosition();
    Vector2 directionToPlayer = Vector2Normalize(Vector2Subtract(playerPosition, position));

//    if(Vector2Distance(playerPosition, position) > Radius)
//    {
    position = Vector2Add(position, Vector2Scale(directionToPlayer, speed * deltaTime));

    for (BasicEnemy *enemy: enemies) {
        if (enemy == this) {
            continue;
        }

        Vector2 enemyPosition = enemy->GetPosition();
        if (Vector2Distance(enemyPosition, position) <= Radius * 2 + AvoidanceBonus) {
            Vector2 directionToEnemy = Vector2Normalize(Vector2Subtract(enemyPosition, position));
            position = Vector2Subtract(position, Vector2Scale(directionToEnemy, speed * deltaTime));
        }
    };
//    }
}

void BasicEnemy::MarkDying() {
    timeDying = 0;
    isDying = true;
}

void BasicEnemy::MarkForDeletion() {
    toDelete = true;
}
