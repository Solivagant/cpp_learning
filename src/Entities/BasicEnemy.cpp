//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include <iostream>
#include "BasicEnemy.h"
#include "../../lib/raymath.h"

BasicEnemy::BasicEnemy(Vector2 initialPosition) {
    position = initialPosition;
    speed = InitialSpeed;
}

void BasicEnemy::Draw() {
    DrawCircleV(position, Radius, RED);
}

// Moves towards the player
void BasicEnemy::Move(float deltaTime, Player* player, std::vector<BasicEnemy*> enemies) {
    Vector2 playerPosition = player->GetPosition();
    Vector2 directionToPlayer = Vector2Normalize(Vector2Subtract(playerPosition, position));

    if(Vector2Distance(playerPosition, position) > Radius * 2)
    {
        position = Vector2Add(position, Vector2Scale(directionToPlayer, speed * deltaTime));

        for (BasicEnemy *enemy: enemies) {
            if (enemy == this) {
                continue;
            }

            Vector2 enemyPosition = enemy->GetPosition();
            if(Vector2Distance(enemyPosition, position) <= Radius * 2)
            {
                Vector2 directionToEnemy = Vector2Normalize(Vector2Subtract(enemyPosition, position));
                position = Vector2Subtract(position, Vector2Scale(directionToEnemy, speed * deltaTime) );
            }
        };
    }
}

void BasicEnemy::MarkForDeletion() {
    toDelete = true;
}
