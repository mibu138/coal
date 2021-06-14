#include "linalg.h"
#include "util.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define CROSS(dest,v1,v2) \
    dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
    dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
    dest[2]=v1[0]*v2[1]-v1[1]*v2[0];

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define SUB(dest,v1,v2) \
    dest[0]=v1[0]-v2[0]; \
    dest[1]=v1[1]-v2[1]; \
    dest[2]=v1[2]-v2[2];

_Static_assert(sizeof(Vec3) == 12, "Bad size for Vec3. Should be exactly 3 floats wide.");

static Vec2 coal_Mult_Mat2Vec2(Mat2 m, Vec2 v)
{
    float x = m.x00 * v.x + m.x01 * v.y;
    v.y = m.x10 * v.x + m.x11 * v.y;
    v.x = x;
    return v;
}

Mat4 coal_Ident_Mat4(void)
{
    Mat4 m = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
    return m;
};

Mat4 coal_BuildPerspective(const float nearDist, const float farDist)
{
    /*
     * Formula: 
     * 1   0   0   0
     * 0   1   0   0
     * 0   0   A  -1
     * 0   0   B   0
     *
     * A = f / (n - f)
     * B = (f * n) / (n - f)
     *
     * f = distance to far clip plane from camera
     * n = distance to close clip plane from camera
     *
     * Note: n cannot be 0!
     * TODO: derive this for yourself.
     */
    assert(nearDist > 0.00001);
    const float f = farDist;
    const float n = nearDist;
    const float A = f / (n - f);
    const float B = f * n / (n - f);
    Mat4 m = {
        1,   0,  0,  0,
        0,  -1,  0,  0,
        0,   0,  A,  -1,
        0,   0,  B,  0
    };
    return m;
}

Vec2 coal_Rotate_Vec2(float angle, Vec2 v)
{
    Mat2 rot = {
        .x00 =  cos(angle),
        .x01 = -sin(angle),
        .x10 =  sin(angle),
        .x11 =  cos(angle)
    };
    return coal_Mult_Mat2Vec2(rot, v);
}

Vec3 coal_RotateY_Vec3(float angle, Vec3 v)
{
    Mat4 m = coal_Ident_Mat4();
    m = coal_RotateY_Mat4(angle, m);
    return coal_Mult_Mat4Vec3(m, v);
}

Vec3 coal_Add_Vec3(const Vec3 a, const Vec3 b)
{
    return (Vec3){
        a.e[0] + b.e[0], 
        a.e[1] + b.e[1], 
        a.e[2] + b.e[2]};
}

Vec3 coal_Sub_Vec3(Vec3 a, Vec3 b)
{
    return (Vec3){
        a.x - b.x,
        a.y - b.y,
        a.z - b.z};
}

float coal_Dot(Vec3 a, Vec3 b)
{
    return a.e[0] * b.e[0] 
         + a.e[1] * b.e[1] 
         + a.e[2] * b.e[2];
}

Vec3 coal_Cross(Vec3 a, Vec3 b)
{
    Vec3 v;
    v.e[0] = a.e[1] * b.e[2] - a.e[2] * b.e[1];
    v.e[1] = a.e[2] * b.e[0] - a.e[0] * b.e[2];
    v.e[2] = a.e[0] * b.e[1] - a.e[1] * b.e[0];
    return v;
}

Vec3 coal_Mult_Mat4Vec3(Mat4 m, Vec3 v)
{
    Vec3 out;
    for (int i = 0; i < 3; i++) 
    {
        out.e[i] = 0.0;
        for (int j = 0; j < 3; j++) 
        {
            out.e[i] += m.e[j][i] * v.e[j];
        }
    }
    return out;
}

Vec4 coal_Mult_Mat4Vec4(Mat4 m, Vec4 v)
{
    Vec4 out;
    for (int i = 0; i < 4; i++) 
    {
        out.e[i] = 0.0;
        for (int j = 0; j < 4; j++) 
        {
            out.e[i] += m.e[j][i] * v.e[j];
        }
    }
    return out;
}

Mat4 coal_Mult_Mat4(Mat4 a, Mat4 b)
{
    Mat4 out;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
        {
            out.e[i][j] = 0;
            for (int k = 0; k < 4; k++) 
                out.e[i][j] += a.e[i][k] * b.e[k][j];
        }
    return out;
}

Mat4 coal_BuildRotate(float angle, Vec3 axis)
{
    const float x = axis.e[0];
    const float y = axis.e[1];
    const float z = axis.e[2];
    const float a = angle;
    const Vec3 col1 = {
        cos(a) + x*x*(1 - cos(a)),
        x*y*(1 - cos(a)) + z*sin(a),
        z*x*(1 - cos(a)) - y*sin(a)
    };
    const Vec3 col2 = {
        x*y*(1 - cos(a)) - z*sin(a),
        cos(a) + y*y*(1 - cos(a)),
        z*y*(1 - cos(a)) + x*sin(a)
    };
    const Vec3 col3 = {
        x*z*(1 - cos(a)) + y*sin(a),
        y*z*(1 - cos(a)) - x*sin(a),
        cos(a) + z*z*(1 - cos(a))
    };
    return coal_BuildFromBasis_Mat4(col1.e, col2.e, col3.e);
}

Mat4 coal_RotateY_Mat4(float angle, Mat4 m)
{
    const float c = cos(angle);
    const float s = sin(angle);
    const Mat4 rot = {
        c, 0,-s, 0,
        0, 1, 0, 0,
        s, 0, c, 0,
        0, 0, 0, 1,
    };
    return coal_Mult_Mat4(rot, m);
}

Mat4 coal_RotateZ_Mat4(float angle, Mat4 m)
{
    const float c = cos(angle);
    const float s = sin(angle);
    const Mat4 rot = {
        c, s, 0, 0,
       -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
    return coal_Mult_Mat4(rot, m);
}

Mat4 coal_Translate_Mat4(const Vec3 t, const Mat4 m)
{
    const Mat4 trans = {
        1,     0,   0, 0,
        0,     1,   0, 0,
        0,     0,   1, 0,
        t.e[0], t.e[1], t.e[2], 1
    };
    return coal_Mult_Mat4(m, trans);
}

Mat4 coal_BuildFromBasis_Mat4(const float x[3], const float y[3], const float z[3])
{
    const Mat4 m = (Mat4){
        x[0], x[1], x[2], 0,
        y[0], y[1], y[2], 0,
        z[0], z[1], z[2], 0,
        0,       0,    0, 1
    };
    return m;
}

Mat4 coal_LookAt(const Vec3 pos, const Vec3 target, const Vec3 up)
{
    Vec3 temp = coal_Sub_Vec3(target, pos);
    const Vec3 dir = coal_Normalize_Vec3(temp);
    temp = coal_Cross(dir, up);
    const Vec3 x = coal_Normalize_Vec3(temp);
    temp = coal_Cross(x, dir);
    const Vec3 y = coal_Normalize_Vec3(temp);
    const Vec3 z = coal_Scale_Vec3(-1, dir);
    Mat4 m = coal_BuildFromBasis_Mat4(x.e, y.e, z.e);
    m = coal_Translate_Mat4(pos, m);
    return m;
}

void coal_LookAtInverse(const Mat4 m, float pivotDistance, Vec3* pos, Vec3* target, Vec3* up)
{
    *pos = coal_GetTranslation_Mat4(m);
    Vec3 z = coal_GetLocalZ_Mat4(m);
    Vec3 dir = coal_Scale_Vec3(-pivotDistance, z);
    *target = coal_Add_Vec3(dir, *pos);
    *up = coal_GetLocalY_Mat4(m);
}

Mat4 coal_LookAt_old(const Vec3 pos, const Vec3 target, const Vec3 up)
{
    Vec3 temp = coal_Sub_Vec3(target, pos);
    const Vec3 dir = coal_Normalize_Vec3(temp);
    temp = coal_Cross(dir, up);
    const Vec3 x = coal_Normalize_Vec3(temp);
    temp = coal_Cross(x, dir);
    const Vec3 y = coal_Normalize_Vec3(temp);
    const Vec3 z = coal_Scale_Vec3(-1, dir);
    Mat4 m = coal_BuildFromBasis_Mat4(x.e, y.e, z.e);
    m = coal_Transpose_Mat4(m);
    m = coal_Translate_Mat4(coal_Scale_Vec3(-1, pos), m);
    //m = coal_Translate_Mat4(*pos, &m);
    return m;
}

Mat4 coal_ScaleUniform_Mat4(const float s, Mat4 m)
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            m.e[i][j] *= s;
        }
    }
    return m;
}

Mat4 coal_ScaleNonUniform_Mat4(const Vec3 s, Mat4 m)
{
    for (int i = 0; i < 3; i++) 
    {
        m.e[i][i] = s.e[i];
    }
    return m;
}

Mat4 coal_Transpose_Mat4(const Mat4 m)
{
    Mat4 out;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            out.e[i][j] = m.e[j][i];
        }  
    }
    return out;
}

Vec2 coal_Translate_Vec2(const Vec2 t, Vec2 v)
{
    v.x += t.x;
    v.y += t.y;
    return v;
}

Vec2 coal_Scale_Vec2(const float s, Vec2 v)
{
    v.x *= s;
    v.y *= s;
    return v;
}

float coal_Distance(const Vec2 a, const Vec2 b)
{
    return coal_Length(coal_Subtract(a, b));
}

float coal_Length(const Vec2 v)
{
    return sqrt(coal_Length2(v));
}

float coal_Length2(const Vec2 v)
{
    return v.x * v.x + v.y * v.y;
}

Vec2 coal_Add(const Vec2 v1, Vec2 v2)
{
    v2.x += v1.x;
    v2.y += v1.y;
    return v2;
}

Vec2 coal_Subtract(const Vec2 v1, const Vec2 v2)
{
    Vec2 v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

float coal_RandNeg(void)
{
    float r = rand() / (float)RAND_MAX;
    return r * 2 - 1;
}

float coal_Det2x2(const Mat2 m)
{
    return m.x00 * m.x11 - m.x10 * m.x01;
}

Vec2 coal_PolarToCart(const float angle, const float radius)
{
    Vec2 v = {
        cos(angle) * radius,
        sin(angle) * radius
    };
    return v;
}

Vec3 coal_GetTranslation_Mat4(const Mat4 m)
{
    return (Vec3){m.e[3][0], m.e[3][1], m.e[3][2]};
}

Vec3 coal_GetLocalX_Mat4(const Mat4 m)
{
    return (Vec3){
        m.e[0][0]/* + m.e[3][0] */, 
        m.e[0][1]/* + m.e[3][1] */, 
        m.e[0][2]/* + m.e[3][2] */};
}

Vec3 coal_GetLocalY_Mat4(const Mat4 m)
{
    return (Vec3){
        m.e[1][0]/* + m.e[3][0] */, 
        m.e[1][1]/* + m.e[3][1] */, 
        m.e[1][2]/* + m.e[3][2] */};
}

Vec3 coal_GetLocalZ_Mat4(const Mat4 m)
{
    return (Vec3){
        m.e[2][0]/* + m.e[3][0] */, 
        m.e[2][1]/* + m.e[3][1] */, 
        m.e[2][2]/* + m.e[3][2] */};
}

float coal_Length_Vec3(const Vec3 v)
{
    return sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

float coal_Length_Vec4(const Vec4 v)
{
    return sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2] + v.e[3] * v.e[3]);
}

Vec3 coal_Scale_Vec3(const float s, const Vec3 v)
{
    return (Vec3){v.e[0] * s, v.e[1] * s, v.e[2] * s};
}

Vec3 coal_Normalize_Vec3(const Vec3 v)
{
    const float m = coal_Length_Vec3(v);
    assert(m != 0.0);
    return (Vec3){v.e[0] / m, v.e[1] / m, v.e[2] / m};
}

Vec4 coal_Normalize_Vec4(const Vec4 v)
{
    const float m = coal_Length_Vec4(v);
    assert(m != 0.0);
    return (Vec4){v.e[0] / m, v.e[1] / m, v.e[2] / m, v.e[3] / m};
}

Mat4 coal_Invert4x4(const Mat4 mat)
{
    const float* const m = (float*)mat.e;
    float inv[16];

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    assert( det != 0 );

    det = 1.0 / det;

    Mat4 out;
    float* const outx = (float*)out.e;
    for (int i = 0; i < 16; i++) 
    {
        outx[i] = inv[i] * det;
    }
    return out;
}

void coal_SetSeed(unsigned int seed)
{
    srand(seed);
}

float coal_Rand(void)
{
    return (float)rand() / (float)RAND_MAX;
}

float coal_RandRange(float min, float max)
{
    const float width = max - min;
    float x = (float)rand() / (float)RAND_MAX;
    x = x * width + min;
    return x;
}

Vec3 coal_RandVec3(float min, float max)
{
    const float width = max - min;
    float x = (float)rand() / (float)RAND_MAX;
    float y = (float)rand() / (float)RAND_MAX;
    float z = (float)rand() / (float)RAND_MAX;
    x = x * width + min; 
    y = y * width + min; 
    z = z * width + min; 
    return (Vec3){x, y, z};
}

#define EPSILON 0.000001
// Moller & Trumbore triangle intersection algorithm
// this culls all triangles facing away
int coal_IntersectTriangle2(const Vec3 orig, const Vec3 dir, 
        const Vec3 vert0, const Vec3 vert1, const Vec3 vert2,
        float* t, float* u, float* v)
{
    const Vec3 edge1 = coal_Sub_Vec3(vert1, vert0);
    const Vec3 edge2 = coal_Sub_Vec3(vert2, vert0);
    const Vec3 pvec  = coal_Cross(dir, edge2);
    const float det  = coal_Dot(edge1, pvec);
    if (det < EPSILON) 
        return 0;
    const Vec3 tvec  = coal_Sub_Vec3(orig, vert0);
    *u = coal_Dot(tvec, pvec);
    if (*u < 0.0 || *u > det) // may have branch detection issues
        return 0; 
    const Vec3 qvec  = coal_Cross(tvec, edge1);
    *v = coal_Dot(dir, qvec);
    if (*v < 0.0 || *u + *v > det) 
        return 0;
    *t = coal_Dot(edge2, qvec);
    const float inv_det = 1.0 / det;
    *t *= inv_det;
    *u *= inv_det;
    *v *= inv_det;
    return 1;
}

Vec3 coal_Lerp_Vec3(const Vec3 a, const Vec3 b, const float t)
{
    assert(t >= 0.0 && t <= 1.0);
    Vec3 v;
    v.e[0] = a.e[0] * (1.0 - t) + b.e[0] * t;
    v.e[1] = a.e[1] * (1.0 - t) + b.e[1] * t;
    v.e[2] = a.e[2] * (1.0 - t) + b.e[2] * t;
    return v;
}
