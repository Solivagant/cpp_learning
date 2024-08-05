//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "BasicEnemy.h"
#include "EntityResolver.h"

BasicEnemy::BasicEnemy(EntityResolver* resolver, Vector2 initialPosition) {
    // Define the player character
    position = initialPosition;
    speed = 100.0f;
}

void BasicEnemy::Draw() {
    DrawRectangle(position.x, position.y, 20, 20, RED);
}

void BasicEnemy::Move(float deltaTime) {

}
