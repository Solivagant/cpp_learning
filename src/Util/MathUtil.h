//
// Created by Geraldo Nascimento on 05/08/2024.
//

#ifndef CPP_LEARNING_MATHUTIL_H
#define CPP_LEARNING_MATHUTIL_H

#include "../../lib/raylib.h"
#include "../../lib/raymath.h"

Vector2 CalculateCenter(Vector2 vectorA, Vector2 vectorB);
Vector2 NormalizeVector(Vector2 vector);

//Template definitions have to be in header files.
//An alternative solution is including the definition in a
// separate file included at the end of the header file.
//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
template<typename T>
bool CompareByDistance(T* a, T* b, const Vector2 &point) {
    float distanceA = Vector2Distance(a->GetPosition(), point);
    float distanceB = Vector2Distance(b->GetPosition(), point);
    return distanceA < distanceB;
}

#endif //CPP_LEARNING_MATHUTIL_H
