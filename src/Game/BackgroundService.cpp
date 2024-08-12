//
// Created by Geraldo Nascimento on 07/08/2024.
//

#include "BackgroundService.h"

void BackgroundService::Init(int screenWidth, int screenHeight, PlayerData* playerData) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    Image gradient1 = GenImageGradientLinear(screenWidth, screenHeight / 2.0f, 0, PURPLE, BLUE);
    Image gradient2 = GenImageGradientLinear(screenWidth, screenHeight / 2.0f, 0, BLUE, PURPLE);

    //TODO would be cool to have a system always creating new gradients as you approach the edge
    background1 = LoadTextureFromImage(gradient1);
    background2 = LoadTextureFromImage(gradient2);
    UnloadImage(gradient1);
    UnloadImage(gradient2);


    const rxcpp::observable<Vector2> observable = *playerData->GetPositionObservable();
    observable.subscribe(
            [this](Vector2 playerPos) {
                this->playerPos = playerPos;
            });
}

void BackgroundService::Draw() {
    DrawTexture(background1, playerPos.x - screenWidth / 2.0f,playerPos.y - screenHeight / 2.0f, LIGHTGRAY);
    DrawTexture(background2, playerPos.x - screenWidth / 2.0f,playerPos.y, LIGHTGRAY);
}

void BackgroundService::Unload() {
    UnloadTexture(background1);
    UnloadTexture(background2);
}


