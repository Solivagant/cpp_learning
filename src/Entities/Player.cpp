//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "../../lib/raylib.h"
#include "Player.h"

static const float maxHoldTime = 1.5;
static const float speedBoost = 1.0f;
static const float timePerFire = 0.25f;

bool Player::IsInputDownHeld() const { return IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S); }

bool Player::IsInputUpHeld() const { return IsKeyDown(KEY_UP) || IsKeyDown(KEY_W); }

bool Player::IsInputLeftHeld() const { return IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A); }

bool Player::IsInputRightHeld() const { return IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D); }

Player::Player(PlayerData* playerData, GameData* gameData, Vector2 initialPosition) {
    this->initialPosition = initialPosition;
    this->playerData = playerData;
    this->gameData = gameData;
    position = initialPosition;
    speed = InitialSpeed;
}

void Player::Move(float deltaTime) {
    if (playerData->IsDead()) return;

    if (IsInputRightHeld()) {
        position.x += speed * deltaTime;
        timeMoveHeld += deltaTime;
    }

    if (IsInputLeftHeld()) {
        position.x -= speed * deltaTime;
        timeMoveHeld += deltaTime;
    }

    if (IsInputUpHeld()) {
        position.y -= speed * deltaTime;
        timeMoveHeld += deltaTime;
    }

    if (IsInputDownHeld()) {
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

    if (timeMoveHeld > 0 && timeMoveHeld < maxHoldTime) {
        speed += speedBoost;
    }
}

void Player::Draw() {
    if (!playerData->IsDead()) {
        DrawCircleV(position, Radius, GREEN);

        float segmentSize = (float)gameData->GetScreenWidth() / playerData->GetMaxHealth();

        DrawRectangleV(Vector2{0, (float)gameData->GetScreenHeight() - 20}, Vector2{(float)segmentSize * (float)playerData->GetHealth(), 20}, GREEN);
    }

}

bool Player::Fire(float deltaTime) {
    timeToFire += deltaTime;
    if (IsMouseButtonDown(0)) {
        if (timeToFire > timePerFire) {
            timeToFire = 0;
            return true;
        }
    }
    return false;
}

Vector2 Player::GetFirePosition() {
    return GetMousePosition();
}

void Player::Respawn() {
    position = initialPosition;
    playerData->SetHealth(playerData->GetMaxHealth());
}

void Player::DealDamage(int amount) {
    playerData->SetHealth(playerData->GetHealth()-amount);
}
