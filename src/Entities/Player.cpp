//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "Player.h"

Player::Player(Vector2 initialPosition) {
    // Define the player character
    position = initialPosition;
    speed = 200.0f;
}

//TODO move faster the longer you hold, up to a certain limit
void Player::Move(float deltaTime) {
    // Move player with arrow keys
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) position.x += speed * deltaTime;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) position.x -= speed * deltaTime;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) position.y -= speed * deltaTime;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) position.y += speed * deltaTime;
}

void Player::Draw() {
    DrawCircleV(position, 25, BLUE);
}
