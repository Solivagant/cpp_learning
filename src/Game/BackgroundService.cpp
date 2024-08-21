//
// Created by Geraldo Nascimento on 07/08/2024.
//

#include "BackgroundService.h"

void BackgroundService::Init(int screenWidth, int screenHeight, PlayerData* playerData, GameData* gameData) {
    this->backgroundWidth = screenWidth + 20;
    this->backgroundHeight = screenHeight + 20;
    this->playerData = playerData;
    this->gameData = gameData;
    Image image1 = GenImageGradientLinear(backgroundWidth, this->backgroundHeight, 0, PURPLE, BLUE);
    background1 = LoadTextureFromImage(image1);

    Image image2 = GenImageGradientLinear(backgroundWidth, this->backgroundHeight, 0, PURPLE, BLUE);
    background2 = LoadTextureFromImage(image2);
    UnloadImage(image1);
    UnloadImage(image2);
}

void BackgroundService::Draw(float deltaTime) {
    auto playerPos = playerData->GetPosition();

    if (transitionStarted) {
        transitionTime += deltaTime;
        prevBGAlpha -= 0.05f * transitionTime;
        nextBGAlpha += 0.05f * transitionTime;

        if (prevBGAlpha <= 0) {
            background1 = background2;
            transitionStarted = false;

            prevBGAlpha = 1;
            nextBGAlpha = 0;
        }
    }

    float posX = -10;
    float posY = -10;

    if (gameData->GetCameraFollowsPlayer()){
        posX = playerPos.x - this->backgroundWidth / 2.0f;
        posY = playerPos.y - this->backgroundHeight / 2.0f;
    }

    DrawTexture(background1, posX, posY, Fade(LIGHTGRAY, prevBGAlpha));
    DrawTexture(background2,  posX, posY, Fade(LIGHTGRAY, nextBGAlpha));
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

    background2 = LoadTextureFromImage(image);
    UnloadImage(image);
}

void BackgroundService::Restart() {
    UnloadTexture(background1);
    UnloadTexture(background2);

    Image image1 = GenImageGradientLinear(backgroundWidth, this->backgroundHeight, 0, PURPLE, BLUE);
    background1 = LoadTextureFromImage(image1);

    Image image2 = GenImageGradientLinear(backgroundWidth, this->backgroundHeight, 0, PURPLE, BLUE);
    background2 = LoadTextureFromImage(image2);
    UnloadImage(image1);
    UnloadImage(image2);

    transitionStarted = false;

    prevBGAlpha = 1;
    nextBGAlpha = 0;
}

void BackgroundService::Unload() {
    UnloadTexture(background1);
    UnloadTexture(background2);
}


