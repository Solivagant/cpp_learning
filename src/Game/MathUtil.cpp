//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "MathUtil.h"

Vector2 CalculateCenter(Vector2 vectorA, Vector2 vectorB) {
    //Auto deduces the player type from the initialization
    auto vectorAHalf = Vector2{vectorA.x / 2, vectorA.y / 2};
    auto vectorBHalf = Vector2{vectorB.x / 2, vectorB.y / 2};
    return Vector2Subtract(vectorAHalf, vectorBHalf);
}
