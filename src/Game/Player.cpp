//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "Player.h"
#include "../../lib/raylib.h"

Player::Player(Vector2 initialPosition) {
    // Define the player character
    playerPosition = initialPosition;
    playerSpeed = 200.0f;
}

//TODO move faster the longer you hold, up to a certain limit
void Player::DoMovement(float deltaTime) {
    // Move player with arrow keys
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) playerPosition.x += playerSpeed * deltaTime;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) playerPosition.x -= playerSpeed * deltaTime;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) playerPosition.y -= playerSpeed * deltaTime;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) playerPosition.y += playerSpeed * deltaTime;
}

void Player::DoDraw() {
    DrawCircleV(playerPosition, 25, BLUE);
}
