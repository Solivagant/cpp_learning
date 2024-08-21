//
// Created by Geraldo Nascimento on 07/08/2024.
//

#ifndef CPP_LEARNING_BACKGROUNDSERVICE_H
#define CPP_LEARNING_BACKGROUNDSERVICE_H
#include "../../lib/raylib.h"
#include "../Util/MathUtil.h"
#include "../Stats/PlayerData.h"
#include "GameData.h"
#include <map>

class BackgroundService {
public:
    void Init(int screenWidth, int screenHeight, PlayerData* playerData, GameData* gameData);
    void Draw(float deltaTime);
    void Unload();
    void StartTransition();
    void Restart();
private:
    Texture2D background1;
    Texture2D background2;

    int backgroundWidth;
    int backgroundHeight;
    PlayerData* playerData;
    GameData* gameData;

    bool transitionStarted;
    float prevBGAlpha = 1;
    float nextBGAlpha = 0;
    float transitionTime;

    std::vector<Color> colorsA{YELLOW,
                              GOLD,
                              ORANGE,
                              LIME,
                              DARKGREEN
    };

    std::vector<Color> colorsB{
                              SKYBLUE,
                              BLUE,
                              DARKBLUE,
                              PURPLE,
                              VIOLET,
                              DARKPURPLE
    };
};
#endif //CPP_LEARNING_BACKGROUNDSERVICE_H
