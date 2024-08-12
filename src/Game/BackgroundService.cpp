//
// Created by Geraldo Nascimento on 07/08/2024.
//

#include "BackgroundService.h"

void BackgroundService::Init(int screenWidth, int screenHeight) {
    background = LoadTexture("assets/background.png");
    distance = CalculateCenter(Vector2{(float) background.width, (float) background.height},
                               Vector2{(float) screenWidth, (float) screenHeight});

}

void BackgroundService::Draw() {
    DrawTexture(background, -(int) distance.x, -(int) distance.y, LIGHTGRAY);
}

void BackgroundService::Unload() {
    UnloadTexture(background);
}


