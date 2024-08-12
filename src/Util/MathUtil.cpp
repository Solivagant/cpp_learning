//
// Created by Geraldo Nascimento on 05/08/2024.
//

#include "MathUtil.h"

Vector2 CalculateCenter(Vector2 vectorA, Vector2 vectorB) {
    //Auto deduces the variable type from the initialization
    auto vectorAHalf = Vector2{vectorA.x / 2, vectorA.y / 2};
    auto vectorBHalf = Vector2{vectorB.x / 2, vectorB.y / 2};
    return Vector2Subtract(vectorAHalf, vectorBHalf);
}

Vector2 NormalizeVector(Vector2 vector) {
    float mag = Vector2Length(vector);
    return Vector2{vector.x / mag, vector.y / mag};
}


