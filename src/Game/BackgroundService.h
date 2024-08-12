//
// Created by Geraldo Nascimento on 07/08/2024.
//

#ifndef CPP_LEARNING_BACKGROUNDSERVICE_H
#define CPP_LEARNING_BACKGROUNDSERVICE_H
#include "../../lib/raylib.h"
#include "../Util/MathUtil.h"
#include "../Stats/PlayerData.h"

class BackgroundService {
public:
    void Init(int screenWidth, int screenHeight, PlayerData* playerData);
    void Draw();
    void Unload();
private:
    Texture2D background1;
    Texture2D background2;
    Vector2 distance;
    Vector2 playerPos;
    int screenWidth;
    int screenHeight;
};

#endif //CPP_LEARNING_BACKGROUNDSERVICE_H
