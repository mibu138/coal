#include "m.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef Coal_Vec3 Vec3;
typedef Coal_Mat4 Mat4;

void coal_Mat4_Identity(Mat4 m)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = (i == j ? 1 : 0);
}

void coal_Mult_Mat4(const Mat4 a, const Mat4 b, Mat4 out)
{
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
        {
            out[i][j] = 0;
            for (int k = 0; k < 4; k++) 
                out[i][j] += a[i][k] * b[k][j];
        }
}

void coal_Translate_Mat4(const Vec3 t, const Mat4 m, Mat4 out)
{
    const Mat4 trans = {
        1,     0,   0, 0,
        0,     1,   0, 0,
        0,     0,   1, 0,
        t[0], t[1], t[2], 1
    };
    coal_Mult_Mat4(m, trans, out);
}

void coal_Copy_Mat4(const Mat4 in, Mat4 out)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out[i][j] = in[i][j];
}

void coal_Copy_Vec3(const Vec3 in, Vec3 out)
{
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
}
