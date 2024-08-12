//
// Created by Geraldo Nascimento on 07/08/2024.
//

#ifndef CPP_LEARNING_BACKGROUNDSERVICE_H
#define CPP_LEARNING_BACKGROUNDSERVICE_H
#include "../../lib/raylib.h"
#include "../Util/MathUtil.h"

class BackgroundService {
public:
    void Init(int screenWidth, int screenHeight);
    void Draw();
    void Unload();
private:
    Texture2D background;
    Vector2 distance;
};

#endif //CPP_LEARNING_BACKGROUNDSERVICE_H
