//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "GameData.h"

GameData::GameData(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

int GameData::GetScreenWidth() const {
    return screenWidth;
}

int GameData::GetScreenHeight() const {
    return screenHeight;
}

bool GameData::GetIsRunning() {
    return isRunning;
}

void GameData::SetIsRunning(bool isRunning) {
    GameData::isRunning = isRunning;
}

bool GameData::GetCameraFollowsPlayer()
{
    return cameraFollowsPlayer;
}