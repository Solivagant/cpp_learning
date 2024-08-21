//
// Created by Geraldo Nascimento on 09/08/2024.
//

#ifndef CPP_LEARNING_GAMEDATA_H
#define CPP_LEARNING_GAMEDATA_H

class GameData {
public:
    GameData(int screenWidth, int screenHeight);
    int GetScreenWidth() const;
    int GetScreenHeight() const;
    bool GetIsRunning();
    void SetIsRunning(bool isRunning);
    bool GetCameraFollowsPlayer();
private:
    bool isRunning;
    int screenWidth;
    int screenHeight;
    bool cameraFollowsPlayer = true;
};

#endif //CPP_LEARNING_GAMEDATA_H
