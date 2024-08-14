//
// Created by Geraldo Nascimento on 07/08/2024.
//

#include "BackgroundService.h"

void BackgroundService::Init(int screenWidth, int screenHeight, PlayerData* playerData) {
    this->backgroundWidth = screenWidth + 20;
    this->backgroundHeight = screenHeight + 20;
    this->playerData = playerData;
    Image image = GenImageGradientLinear(backgroundWidth, this->backgroundHeight, 0, PURPLE, BLUE);
    background1 = LoadTextureFromImage(image);

    Image image2 = GenImageGradientLinear(backgroundWidth, this->backgroundHeight, 0, PURPLE, BLUE);
    background3 = LoadTextureFromImage(image2);
    UnloadImage(image2);
}

void BackgroundService::Draw(float deltaTime) {
    auto playerPos = playerData->GetPosition();

    if (transitionStarted) {
        transitionTime += deltaTime;
        prevBGAlpha -= 0.05f * transitionTime;
        nextBGAlpha += 0.05f * transitionTime;

        if (prevBGAlpha <= 0) {
            background1 = background3;
            transitionStarted = false;

            prevBGAlpha = 1;
            nextBGAlpha = 0;
        }
    }

    DrawTexture(background1, playerPos.x - backgroundWidth / 2.0f, playerPos.y - this->backgroundHeight / 2.0f,
                Fade(LIGHTGRAY, prevBGAlpha));

    DrawTexture(background3, playerPos.x - backgroundWidth / 2.0f, playerPos.y - this->backgroundHeight / 2.0f,
                Fade(LIGHTGRAY, nextBGAlpha));
}

void BackgroundService::StartTransition() {
    transitionStarted = true;
    transitionTime = 0;

    int colorA = GetRandomValue(0, colorsA.size() - 1);
    int colorB = GetRandomValue(0, colorsB.size() - 1);

    int imageType = GetRandomValue(0, 2);

    Image image;

    switch (imageType) {
        case 0:
            image = GenImageGradientLinear(backgroundWidth, this->backgroundHeight, 0, colorsA[colorA],
                                           colorsB[colorB]);
            break;
        case 1:
            image = GenImageGradientSquare(backgroundWidth, this->backgroundHeight, 0, colorsA[colorA],
                                           colorsB[colorB]);
            break;
        case 2:
            image = GenImageGradientRadial(backgroundWidth, this->backgroundHeight, 0, colorsA[colorA],
                                           colorsB[colorB]);
            break;
        default:
            break;
    }

    background3 = LoadTextureFromImage(image);
    UnloadImage(image);
}

void BackgroundService::Unload() {
    UnloadTexture(background1);
    UnloadTexture(background3);
}


