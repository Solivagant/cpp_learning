//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "BasicEnemy.h"
#include "EntityResolver.h"
#include "../../lib/raymath.h"

BasicEnemy::BasicEnemy(EntityResolver *resolver, Vector2 initialPosition) {
    entityResolver = resolver;
    position = initialPosition;
    speed = 100.0f;
}

void BasicEnemy::Draw() {
    DrawRectangle(position.x, position.y, 20, 20, RED);
}

// Moves towards the player
void BasicEnemy::Move(float deltaTime) {
    Vector2 directionToPlayer = Vector2Normalize(Vector2Subtract(entityResolver->GetPlayer()->GetPosition(), position));
    position = Vector2Add(position, Vector2Scale(directionToPlayer, speed * deltaTime));



}
