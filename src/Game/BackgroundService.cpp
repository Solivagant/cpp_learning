//
// Created by Geraldo Nascimento on 07/08/2024.
//

#include "BackgroundService.h"

void BackgroundService::Init(int screenWidth, int screenHeight, PlayerData* playerData) {
    this->backgroundWidth = screenWidth + 20;
    this->backgroundHeight = screenHeight + 20;
    this->playerData = playerData;
    Image gradient1 = GenImageGradientLinear(backgroundWidth, this->backgroundHeight / 2.0f, 0, PURPLE, BLUE);
    Image gradient2 = GenImageGradientLinear(backgroundWidth, this->backgroundHeight / 2.0f, 0, BLUE, PURPLE);

    background1 = LoadTextureFromImage(gradient1);
    background2 = LoadTextureFromImage(gradient2);
    UnloadImage(gradient1);
    UnloadImage(gradient2);
}

void BackgroundService::Draw() {
    auto playerPos = playerData->GetPosition();

    DrawTexture(background1, playerPos.x - backgroundWidth / 2.0f , playerPos.y - this->backgroundHeight / 2.0f, LIGHTGRAY);
    DrawTexture(background2, playerPos.x - backgroundWidth / 2.0f, playerPos.y, LIGHTGRAY);
}

void BackgroundService::Unload() {
    UnloadTexture(background1);
    UnloadTexture(background2);
}


