#ifndef M_MATH_H
#define M_MATH_H

#include <math.h>

typedef union Vec2 {
    float e[2];
    struct {
        float x;
        float y;
    };
} Vec2;

typedef union Vec3 {
    float e[3];
    struct {
        float x;
        float y;
        float z;
    };
} Vec3;

typedef struct Vec4 {
    float e[4];
    struct {
        float x; float y; float z; float w;
    };
} Vec4;

typedef struct Mat2 {
    float x00, x01, 
          x10, x11;
} Mat2;

typedef struct Mat3 {
    float e[3][3];
} Mat3;

typedef struct Mat4 {
    float e[4][4];
} Mat4;

typedef struct Ray {
    Vec2 orig;
    Vec2 dir;
} Ray;

typedef struct Segment {
    Vec2 A;
    Vec2 B;
} Segment;

Mat4 coal_Ident_Mat4(void);
Mat4 coal_BuildPerspective(float nearDist, float farDist);
Vec3 coal_GetLocalZ_Mat4(Mat4 m);
Vec3 coal_GetTranslation_Mat4(Mat4 m);
Vec3 coal_Add_Vec3(Vec3 a, Vec3 b);
Vec3 coal_Sub_Vec3(Vec3 a, Vec3 b);
Vec3 coal_Normalize_Vec3(Vec3 v);
Vec4 coal_Normalize_Vec4(Vec4 v);
Vec3 coal_Scale_Vec3(float s, Vec3 v);
Vec3 coal_Cross(Vec3 a, Vec3 b);
Mat4 coal_LookAt(Vec3 pos, Vec3 target, Vec3 up);
void coal_Rotate_Vec2(float angle /* radians */, Vec2);
Mat4 coal_RotateY_Mat4(float angle, Mat4 m);
Mat4 coal_BuildFromBasis_Mat4(const float x[3], const float y[3], const float z[3]);
Mat4 coal_BuildRotate(float angle, Vec3 axis);
Vec3 coal_RotateY_Vec3(float angle, Vec3 v);
Mat4 coal_RotateZ_Mat4(float angle, Mat4 m);
Mat4 coal_Mult_Mat4(Mat4 a, Mat4 b);
Vec3 coal_Mult_Mat4Vec3(Mat4 m, Vec3 v);
Vec4 coal_Mult_Mat4Vec4(Mat4 m, Vec4 v);
Mat4 coal_Translate_Mat4(Vec3 t, Mat4 m);
Mat4 coal_Transpose_Mat4(Mat4 m);
Mat4 coal_ScaleUniform_Mat4(float s, Mat4 m);
Mat4 coal_ScaleNonUniform_Mat4(Vec3 s, Mat4 m);
Vec2 coal_Translate(Vec2 t, Vec2);
Vec2 coal_Scale(float scale, Vec2);
Vec2 coal_Add(Vec2, Vec2);
float coal_Distance(Vec2 a, Vec2 b);
Vec2 coal_Subtract(Vec2, Vec2);
//returns a random float between 0 and 1
float coal_Rand(void); 
//returns a random float between -1 and 1
float coal_RandNeg(void); 
float coal_Length(Vec2);
float coal_Length2(Vec2);
float coal_Determinant(Mat2);
Vec2  coal_PolarToCart(float angle, float radius);
Mat4  coal_Invert4x4(Mat4);
int   coal_IntersectTriangle(Vec3 orig, const Vec3* dir, 
        const Vec3* vert0, const Vec3* vert1, const Vec3* vert2,
        float* t, float* u, float* v);
Vec3 m_Lerp_Vec3(const Vec3* a, const Vec3* b, const float t);
float coal_Rand(void);
float coal_RandRange(float min, float max);
Vec3 coal_RandVec3(float min, float max);

#endif /* end of include guard: M_MATH_H */
