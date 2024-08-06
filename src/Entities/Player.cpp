//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "Player.h"

static const float maxHoldTime = 1.5;
static const float speedBoost = 1.0f;

Player::Player(Vector2 initialPosition) {
    // Define the player character
    position = initialPosition;
    speed = 200.0f;
}

void Player::Move(float deltaTime) {

    // Move player with arrow keys
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        position.x += speed * deltaTime;
        timeMoveHeld += deltaTime;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        position.x -= speed * deltaTime;
        timeMoveHeld += deltaTime;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        position.y -= speed * deltaTime;
        timeMoveHeld += deltaTime;
    }

    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        position.y += speed * deltaTime;
        timeMoveHeld += deltaTime;
    }

    if (!(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) ||
        IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) ||
        IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) ||
        IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))) {
        timeMoveHeld = 0;
        speed = 200;
    }

    if(timeMoveHeld > 0 && timeMoveHeld < maxHoldTime)
    {
        speed += speedBoost;
    }

}

void Player::Draw() {
    DrawCircleV(position, 25, BLUE);
}
