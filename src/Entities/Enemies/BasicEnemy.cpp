//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "BasicEnemy.h"
#include "../../../lib/raymath.h"

BasicEnemy::BasicEnemy(Vector2 initialPosition) {
    position = initialPosition;
    speed = InitialSpeed;
}

void BasicEnemy::Draw(float deltaTime) {
    if (isDying) {
        timeDying += deltaTime;

        if(isBlowingUp)
        {
            colorAlpha -= 2.5f * timeDying;
            DrawCircleV(position, Radius, Fade(WHITE, colorAlpha));
        }
        else
        {
            colorAlpha -= 10.5f * timeDying;
            DrawCircleV(position, Radius, Fade(RED, colorAlpha));
        }

        if (colorAlpha <= 0) {
            MarkForDeletion();
        }
    }
    else
    {
        DrawCircleV(position, Radius, RED);
    }

}

// Moves towards the player
void BasicEnemy::Move(int playerLevel, float deltaTime, Player *player, std::vector<BasicEnemy *> enemies) {
    Vector2 playerPosition = player->GetPosition();
    Vector2 directionToPlayer = Vector2Normalize(Vector2Subtract(playerPosition, position));

    speed = InitialSpeed + playerLevel * 5;

    position = Vector2Add(position, Vector2Scale(directionToPlayer, speed * deltaTime));

    for (BasicEnemy *enemy: enemies) {
        if (enemy == this) {
            continue;
        }

        Vector2 enemyPosition = enemy->GetPosition();
        if (Vector2Distance(enemyPosition, position) <= Radius * 2 - 3) {
            Vector2 directionToEnemy = Vector2Normalize(Vector2Subtract(enemyPosition, position));
            position = Vector2Subtract(position, Vector2Scale(directionToEnemy, speed * deltaTime));
        }
    };
}

void BasicEnemy::MarkDying(bool isBlowingUp) {
    timeDying = 0;
    isDying = true;
    this->isBlowingUp = isBlowingUp;
}

void BasicEnemy::MarkForDeletion() {
    toDelete = true;
}

void BasicEnemy::DealDamage(int amount) {
    //TODO deal damage
    MarkDying(false);
}


