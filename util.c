#include "util.h"
#include <stdio.h>

void coal_PrintVec2(const Vec2* vec)
{
    printf("x: %f, y: %f\n", vec->x, vec->y);
}

void coal_PrintVec3(const Vec3* vec)
{
    printf("x: %f, y: %f z: %f\n", vec->x[0], vec->x[1], vec->x[2]);
}

void coal_PrintVec4(const Vec4* vec)
{
    printf(" %f, %f, %f, %f\n", vec->x[0], vec->x[1], vec->x[2], vec->x[3]);
}

void coal_PrintMat4(const Mat4 * m)
{
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            printf("%f ", m->x[i][j]);
        }
        printf("\n");
    }
}
