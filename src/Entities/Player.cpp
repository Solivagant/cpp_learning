//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "../../lib/raylib.h"
#include "Player.h"

static const float maxHoldTime = 1.5;
static const float speedBoost = 1.0f;
static const float timePerFire = 0.25f;

Player::Player(Vector2 initialPosition) {
    position = initialPosition;
    speed = InitialSpeed;
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
        speed = InitialSpeed;
    }

    if(timeMoveHeld > 0 && timeMoveHeld < maxHoldTime)
    {
        speed += speedBoost;
    }
}

void Player::Draw() {
    DrawCircleV(position, Radius, GREEN);
}

bool Player::Fire(float deltaTime) {
    timeToFire += deltaTime;
    if(IsMouseButtonDown(0))
    {
        if(timeToFire > timePerFire)
        {
            timeToFire = 0;
            return true;
        }
    }
    return false;
}

Vector2 Player::GetFirePosition() {
    return GetMousePosition();
}