#ifndef COAL_SIMPLE_TYPE_NAMES
#define COAL_SIMPLE_TYPE_NAMES
#endif
#include "util.h"
#include <stdio.h>

void coal_PrintVec2(const Vec2 vec)
{
    printf("x: %f, y: %f\n", vec.x, vec.y);
}

void coal_PrintVec3(const Vec3 vec)
{
    printf("x: %f, y: %f z: %f\n", vec.e[0], vec.e[1], vec.e[2]);
}

void coal_PrintVec4(const Vec4 vec)
{
    printf(" %f, %f, %f, %f\n", vec.e[0], vec.e[1], vec.e[2], vec.e[3]);
}

void coal_PrintMat2(const Mat2 m)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%f ", m.e[i][j]);
        }
        printf("\n");
    }
}

void coal_PrintMat3(const Mat3 m)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f ", m.e[i][j]);
        }
        printf("\n");
    }
}

void coal_PrintMat4(const Mat4 m)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", m.e[i][j]);
        }
        printf("\n");
    }
}

void coal_SprintVec2(char* s, const Vec2 v)
{
    sprintf(s, "x: %f, y: %f", v.x, v.y);
}
