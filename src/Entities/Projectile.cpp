//
// Created by Geraldo Nascimento on 06/08/2024.
//

#include "Projectile.h"

void Projectile::Init(Vector2 initialPosition, Vector2 targetPosition) {
    targetDirection = Vector2Normalize(Vector2Subtract(targetPosition, initialPosition));;
    position = Vector2Add(initialPosition, Vector2Scale(targetDirection, 30));;

    speed = InitialSpeed;
    timeAlive = 0;
    toDelete = false;
}

void Projectile::Move(float deltaTime) {
    timeAlive += deltaTime;
    position = Vector2Add(position, Vector2Scale(targetDirection, speed  * deltaTime));

    if(timeAlive > TimeToLive)
    {
        MarkForDeletion();
    }
}

void Projectile::Draw() {
    DrawCircleV(position, Radius, ORANGE);
}

void Projectile::MarkForDeletion() {
    toDelete = true;
}