//
// Created by Geraldo Nascimento on 07/08/2024.
//

#include "Background.h"

void Background::Init(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    background = LoadTexture("assets/background.png");
    distance = CalculateCenter(Vector2{(float) background.width, (float) background.height},
                               Vector2{(float) screenWidth, (float) screenHeight});

}

void Background::Draw() {
    DrawTexture(background, -(int) distance.x, -(int) distance.y, WHITE);
}

void Background::Unload() {
    UnloadTexture(background);
}


