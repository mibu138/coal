#define COAL_SIMPLE_TYPE_NAMES
#include "generics.h"
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

#ifndef WIN32
_Static_assert(sizeof(Vec3) == 12, "Bad size for Vec3. Should be exactly 3 reals wide.");
#endif

Vec2 coal_Mult_Mat2Vec2(Mat2 m, Vec2 v)
{
    real x = m.x00 * v.x + m.x01 * v.y;
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

Mat4 coal_BuildPerspective(const real nearDist, const real farDist)
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
    const real f = farDist;
    const real n = nearDist;
    const real A = f / (n - f);
    const real B = f * n / (n - f);
    Mat4 m = {
        1,   0,  0,  0,
        0,  -1,  0,  0,
        0,   0,  A,  -1,
        0,   0,  B,  0
    };
    return m;
}

Mat2 coal_Rotate_Mat2(real a, Mat2 m)
{
    Coal_Mat2 o = {cos(a), -sin(a), sin(a), cos(a)};
    return coal_mul(o, m);
}

Vec2 coal_Rotate_Vec2(real angle, Vec2 v)
{
    Mat2 rot = {
        .x00 =  cos(angle),
        .x01 = -sin(angle),
        .x10 =  sin(angle),
        .x11 =  cos(angle)
    };
    return coal_Mult_Mat2Vec2(rot, v);
}

Vec3 coal_RotateY_Vec3(real angle, Vec3 v)
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

real coal_Dot(Vec3 a, Vec3 b)
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

Vec3 coal_Mult_Mat3Vec3(Mat3 m, Vec3 v)
{
    Vec3 out;
    for (int i = 0; i < 3; i++) {
        out.e[i] = 0.0;
        for (int j = 0; j < 3; j++) {
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

Mat4 coal_BuildRotate(real angle, Vec3 axis)
{
    const real x = axis.e[0];
    const real y = axis.e[1];
    const real z = axis.e[2];
    const real a = angle;
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

Mat4 coal_RotateY_Mat4(real angle, Mat4 m)
{
    const real c = cos(angle);
    const real s = sin(angle);
    const Mat4 rot = {
        c, 0,-s, 0,
        0, 1, 0, 0,
        s, 0, c, 0,
        0, 0, 0, 1,
    };
    return coal_Mult_Mat4(rot, m);
}

Mat4 coal_RotateZ_Mat4(real angle, Mat4 m)
{
    const real c = cos(angle);
    const real s = sin(angle);
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

Mat4 coal_BuildFromBasis_Mat4(const real x[3], const real y[3], const real z[3])
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

void coal_LookAtInverse(const Mat4 m, real pivotDistance, Vec3* pos, Vec3* target, Vec3* up)
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

Mat4 coal_ScaleUniform_Mat4(const real s, Mat4 m)
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

Vec2 coal_Scale_Vec2(const real s, Vec2 v)
{
    v.x *= s;
    v.y *= s;
    return v;
}

real coal_Distance(const Vec2 a, const Vec2 b)
{
    return coal_Length_Vec2(coal_Subtract(a, b));
}

real coal_Length_Vec2(const Vec2 v)
{
    return sqrt(coal_Length2_Vec2(v));
}

real coal_Length2_Vec2(const Vec2 v)
{
    return v.x * v.x + v.y * v.y;
}

Vec2 coal_Add(Vec2 v1, Vec2 v2)
{
    v2.x += v1.x;
    v2.y += v1.y;
    return v2;
}

Vec2 coal_Add_Vec2(const Vec2 v1, Vec2 v2)
{
    return coal_Add(v1, v2);
}

Vec2 coal_Subtract(const Vec2 v1, const Vec2 v2)
{
    Vec2 v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

Vec2 coal_Sub_Vec2(const Vec2 v1, const Vec2 v2)
{
    return coal_Subtract(v1, v2);
}

real coal_RandNeg(void)
{
    real r = rand() / (real)RAND_MAX;
    return r * 2 - 1;
}

real coal_Determinant_Mat2(const Mat2 m)
{
    return m.x00 * m.x11 - m.x10 * m.x01;
}

Vec2 coal_PolarToCart(const real angle, const real radius)
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

real coal_Length_Vec3(const Vec3 v)
{
    return sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

real coal_Length_Vec4(const Vec4 v)
{
    return sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2] + v.e[3] * v.e[3]);
}

Vec3 coal_Scale_Vec3(const real s, const Vec3 v)
{
    return (Vec3){v.e[0] * s, v.e[1] * s, v.e[2] * s};
}

Vec3 coal_Normalize_Vec3(const Vec3 v)
{
    const real m = coal_Length_Vec3(v);
    assert(m != 0.0);
    return (Vec3){v.e[0] / m, v.e[1] / m, v.e[2] / m};
}

Vec4 coal_Normalize_Vec4(const Vec4 v)
{
    const real m = coal_Length_Vec4(v);
    assert(m != 0.0);
    return (Vec4){v.e[0] / m, v.e[1] / m, v.e[2] / m, v.e[3] / m};
}

Mat3 coal_Invert3x3(const Mat3 mat)
{
    const float (*m)[3] = mat.e;

    double det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
                 m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                 m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

    double invdet = 1 / det;

    Mat3 out; 
    float (*minv)[3] = out.e;
    minv[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
    minv[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
    minv[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
    minv[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
    minv[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
    minv[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
    minv[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
    minv[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
    minv[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;
    return out;
}

Mat4 coal_Invert4x4(const Mat4 mat)
{
    const real* const m = (real*)mat.e;
    real inv[16];

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

    real det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    assert( det != 0 );

    det = 1.0 / det;

    Mat4 out;
    real* const outx = (real*)out.e;
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

real coal_Rand(void)
{
    return (real)rand() / (real)RAND_MAX;
}

real coal_RandRange(real min, real max)
{
    const real width = max - min;
    real x = (real)rand() / (real)RAND_MAX;
    x = x * width + min;
    return x;
}

Vec3 coal_Rand_Vec3(real min, real max)
{
    const real width = max - min;
    real x = (real)rand() / (real)RAND_MAX;
    real y = (real)rand() / (real)RAND_MAX;
    real z = (real)rand() / (real)RAND_MAX;
    x = x * width + min;
    y = y * width + min;
    z = z * width + min;
    return (Vec3){x, y, z};
}

Vec3 coal_Lerp_Vec3(const Vec3 a, const Vec3 b, const real t)
{
    assert(t >= 0.0 && t <= 1.0);
    Vec3 v;
    v.e[0] = a.e[0] * (1.0 - t) + b.e[0] * t;
    v.e[1] = a.e[1] * (1.0 - t) + b.e[1] * t;
    v.e[2] = a.e[2] * (1.0 - t) + b.e[2] * t;
    return v;
}

Vec2 coal_lerp_vec2(const Vec2 a, const Vec2 b, const real t)
{
    assert(t >= 0.0 && t <= 1.0);
    Vec2 v;
    v.e[0] = a.e[0] * (1.0 - t) + b.e[0] * t;
    v.e[1] = a.e[1] * (1.0 - t) + b.e[1] * t;
    return v;
}

real coal_segment_length(Segment seg)
{
    Vec2 diff = coal_Sub_Vec2(seg.B, seg.A);
    return coal_Length_Vec2(diff);
}

void coal_get_samples_along_line_segment(Segment seg, real rad, Vec2* buf, int max_samples, int* sample_count)
{
    assert(max_samples > 0);
    assert(rad > 0.0);
    // always sample at the segment beginning
    int i = 1;
    real seglen = coal_segment_length(seg);

    buf[0] = seg.A;
    if (rad < seglen)
    {
        const real stepsize = rad / seglen;
        real t = stepsize;
        while (t <= 1.0 && i < max_samples)
        {
            buf[i] = coal_lerp_vec2(seg.A, seg.B, t);
            t += stepsize;
            ++i;
        }
    }
    *sample_count = i;
}
