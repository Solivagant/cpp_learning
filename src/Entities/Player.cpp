//
// Created by Geraldo Nascimento on 05/08/2024.
//

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

    UpdateLevelStream();
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
    if(playerData->GetLevel() > playerLevelCache) {
        UpdateLevelStream();
    }

    if (!playerData->IsDead()) {
        DrawCircleV(position, Radius, GREEN);
    } else {
        DrawCircleV(position, Radius, BLACK);
    }

    DrawUI();
}

void Player::UpdateLevelStream(){
    playerLevelCache = playerData->GetLevel();

    std::stringstream stream;
    if(playerLevelCache < 10)
    {
        stream << " ";
    }
    stream << playerData->GetLevel();

    std::string test = stream.str();
    levelString = new std::vector<char>(begin(test), end(test));
}

bool Player::Fire(float deltaTime) {
    if (playerData->IsDead()) return false;

    timeToFire += deltaTime;
    if (timeToFire * std::clamp(playerData->GetLevel(), 1, 5) > timePerFire) {
        timeToFire = 0;
        return true;
    }
    return false;
}

void Player::Respawn() {
    position = initialPosition;
    playerData->SetHealth(playerData->GetMaxHealth());
    UpdateLevelStream();
}

void Player::DealDamage(int amount) {
    playerData->SetHealth(playerData->GetHealth() - amount);
}

void Player::DrawUI() {
    float healthSegmentSize = (float) gameData->GetScreenWidth() / playerData->GetMaxHealth();
    float xpSegmentSize = (float) gameData->GetScreenWidth() / playerData->GetXPToNextLevel();

    Vector2 bottom = Vector2{0, (float) gameData->GetScreenHeight() - 20};
    Vector2 top = Vector2{0, 0};

    Vector2 topRightCorner = Vector2{(float) gameData->GetScreenWidth() - 20, 0};

    if (gameData->GetCameraFollowsPlayer()) {
        bottom = Vector2{position.x - gameData->GetScreenWidth() / 2,
                         (float) position.y + gameData->GetScreenHeight() / 2 - 20};
        top = Vector2{position.x - gameData->GetScreenWidth() / 2,
                      (float) position.y - gameData->GetScreenHeight() / 2};

        topRightCorner = Vector2{position.x + gameData->GetScreenWidth() / 2 - 20,
                                 (float) position.y - gameData->GetScreenHeight() / 2};
    }

    DrawRectangleV(bottom, Vector2{(float) healthSegmentSize * (float) playerData->GetHealth(), 20}, GREEN);
    DrawRectangleV(top, Vector2{(float) xpSegmentSize * (float) playerData->GetXP(), 20}, ORANGE);
    DrawRectangleV(topRightCorner, Vector2{20, 20}, DARKPURPLE);

    DrawTextEx(GetFontDefault(), levelString->data(), topRightCorner, 20, 1, WHITE);
}

Vector2 Player::GetPosition() {
    return position;
}