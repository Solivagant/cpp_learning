//
// Created by Geraldo Nascimento on 07/08/2024.
//

#ifndef CPP_LEARNING_BACKGROUNDSERVICE_H
#define CPP_LEARNING_BACKGROUNDSERVICE_H
#include "../../lib/raylib.h"
#include "../Util/MathUtil.h"
#include "../Stats/PlayerData.h"
#include <map>

class BackgroundService {
public:
    void Init(int screenWidth, int screenHeight, PlayerData* playerData);
    void Draw(float deltaTime);
    void Unload();
    void StartTransition();
private:
    Texture2D background1;

    Texture2D background3;

    int backgroundWidth;
    int backgroundHeight;
    PlayerData* playerData;

    bool transitionStarted;
    float prevBGAlpha = 1;
    float nextBGAlpha = 0;
    float transitionTime;

    std::vector<Color> colorsA{YELLOW,
                              GOLD,
                              ORANGE,
                              PINK,
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
