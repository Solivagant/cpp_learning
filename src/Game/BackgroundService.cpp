//
// Created by Geraldo Nascimento on 07/08/2024.
//

#include "BackgroundService.h"

void BackgroundService::Init(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    background = LoadTexture("assets/background.png");
    distance = CalculateCenter(Vector2{(float) background.width, (float) background.height},
                               Vector2{(float) screenWidth, (float) screenHeight});

}

void BackgroundService::Draw() {
    DrawTexture(background, -(int) distance.x, -(int) distance.y, WHITE);
}

void BackgroundService::Unload() {
    UnloadTexture(background);
}


