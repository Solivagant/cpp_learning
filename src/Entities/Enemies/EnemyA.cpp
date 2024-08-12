//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "EnemyA.h"
#include "../../../lib/raymath.h"

EnemyA::EnemyA(Vector2 initialPosition) {
    position = initialPosition;
    speed = InitialSpeed;
}

void EnemyA::Draw(float deltaTime) {
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
        //simple calc for now hardcoded to 2 health
        DrawCircleV(position, Radius, BLACK);
        DrawCircleV(position, Radius, Fade(RED, (float)health * 50 / 100));
    }

}

// Moves towards the player
void EnemyA::Move(int playerLevel, float deltaTime, Player *player, std::vector<EnemyA *> enemies) {
    Vector2 playerPosition = player->GetPosition();
    Vector2 directionToPlayer = Vector2Normalize(Vector2Subtract(playerPosition, position));

    speed = InitialSpeed + playerLevel * 5;

    position = Vector2Add(position, Vector2Scale(directionToPlayer, speed * deltaTime));

    for (EnemyA *enemy: enemies) {
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

void EnemyA::MarkDying(bool isBlowingUp) {
    timeDying = 0;
    isDying = true;
    this->isBlowingUp = isBlowingUp;
}

void EnemyA::MarkForDeletion() {
    toDelete = true;
}

void EnemyA::DealDamage(int amount) {
    health = health - amount;
    if(health <= 0) {
        MarkDying(false);
    }
}

void EnemyA::KillFromHittingPlayer() {
    MarkDying(false);
}

int EnemyA::GetHealth() const {
    return health;
}


