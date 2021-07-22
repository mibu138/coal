#ifndef M_MATH_H
#define M_MATH_H

typedef union Coal_Vec2 {
    float e[2];
    struct {
        float x;
        float y;
    };
    struct {
        float width;
        float height;
    };
} Coal_Vec2;

typedef union Coal_Vec3 {
    float e[3];
    struct {
        float x;
        float y;
        float z;
    };
    struct {
        float r;
        float g;
        float b;
    };
} Coal_Vec3;

typedef union Coal_Vec4 {
    float e[4];
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    struct {
        float r;
        float g;
        float b;
        float a;
    };
    struct {
        float offsetx;
        float offsety;
        float width;
        float height;
    };
} Coal_Vec4;

typedef struct Coal_Mat2 {
    float x00, x01, x10, x11;
} Coal_Mat2;

typedef struct Coal_Mat3 {
    float e[3][3];
} Coal_Mat3;

typedef struct Coal_Mat4 {
    float e[4][4];
} Coal_Mat4;

typedef struct Coal_Ray {
    Coal_Vec2 orig;
    Coal_Vec2 dir;
} Coal_Ray;

typedef struct Segment {
    Coal_Vec2 A;
    Coal_Vec2 B;
} Coal_Segment;

#ifndef COAL_NO_SIMPLE_TYPES
typedef Coal_Vec2    Vec2;
typedef Coal_Vec3    Vec3;
typedef Coal_Vec4    Vec4;
typedef Coal_Mat2    Mat2;
typedef Coal_Mat3    Mat3;
typedef Coal_Mat4    Mat4;
typedef Coal_Ray     Ray;
typedef Coal_Segment Segment;
#endif

#define COAL_MAT4_IDENT (Coal_Mat4){\
    1, 0, 0, 0, \
    0, 1, 0, 0, \
    0, 0, 1, 0, \
    0, 0, 0, 1  \
}

Coal_Mat4 coal_Ident_Mat4(void);
Coal_Mat4 coal_BuildPerspective(float nearDist, float farDist);
Coal_Vec3 coal_GetLocalX_Mat4(Coal_Mat4 m);
Coal_Vec3 coal_GetLocalY_Mat4(Coal_Mat4 m);
Coal_Vec3 coal_GetLocalZ_Mat4(Coal_Mat4 m);
Coal_Vec3 coal_GetTranslation_Mat4(Coal_Mat4 m);
Coal_Vec3 coal_Add_Vec3(Coal_Vec3 a, Coal_Vec3 b);
Coal_Vec3 coal_Sub_Vec3(Coal_Vec3 a, Coal_Vec3 b);
Coal_Vec3 coal_Normalize_Vec3(Coal_Vec3 v);
Coal_Vec4 coal_Normalize_Vec4(Coal_Vec4 v);
Coal_Vec3 coal_Scale_Vec3(float s, Coal_Vec3 v);
Coal_Vec3 coal_Cross(Coal_Vec3 a, Coal_Vec3 b);
Coal_Mat4 coal_LookAt(Coal_Vec3 pos, Coal_Vec3 target, Coal_Vec3 up);
void coal_LookAtInverse(const Mat4 m, float pivotDistance, Vec3* pos, Vec3* target, Vec3* up);
Coal_Vec2 coal_Rotate_Vec2(float angle /* radians */, Coal_Vec2);
Coal_Mat4 coal_RotateY_Mat4(float angle, Coal_Mat4 m);
Coal_Mat4 coal_BuildFromBasis_Mat4(const float x[3], const float y[3],
                                        const float z[3]);
Coal_Mat4 coal_BuildRotate(float angle, Coal_Vec3 axis);
Coal_Vec3 coal_RotateY_Vec3(float angle, Coal_Vec3 v);
Coal_Mat4 coal_RotateZ_Mat4(float angle, Coal_Mat4 m);
Coal_Mat4 coal_Mult_Mat4(Coal_Mat4 a, Coal_Mat4 b);
Coal_Vec3 coal_Mult_Mat4Vec3(Coal_Mat4 m, Coal_Vec3 v);
Coal_Vec4 coal_Mult_Mat4Vec4(Coal_Mat4 m, Coal_Vec4 v);
Coal_Mat4 coal_Translate_Mat4(Coal_Vec3 t, Coal_Mat4 m);
Coal_Mat4 coal_Transpose_Mat4(Coal_Mat4 m);
Coal_Mat4 coal_ScaleUniform_Mat4(float s, Coal_Mat4 m);
Coal_Mat4 coal_ScaleNonUniform_Mat4(Coal_Vec3 s, Coal_Mat4 m);
Coal_Vec2 coal_Translate_Vec2(Coal_Vec2 t, Coal_Vec2);
Coal_Vec2 coal_Scale(float scale, Coal_Vec2);
Coal_Vec2 coal_Add(Coal_Vec2, Coal_Vec2);
float     coal_Distance(Coal_Vec2 a, Coal_Vec2 b);
float     coal_Dot(Coal_Vec3 a, Coal_Vec3 b);
Coal_Vec2 coal_Subtract(Coal_Vec2, Coal_Vec2);
// returns a random float between 0 and 1
float     coal_Rand(void);
// returns a random float between -1 and 1
float     coal_RandNeg(void);
float     coal_Length(Coal_Vec2);
float     coal_Length2(Coal_Vec2);
float     coal_Determinant(Coal_Mat2);
Coal_Vec2 coal_PolarToCart(float angle, float radius);
Coal_Mat4 coal_Invert4x4(Coal_Mat4);
int       coal_IntersectTriangle(Coal_Vec3 orig, Coal_Vec3 dir, Coal_Vec3 vert0,
                                 Coal_Vec3 vert1, Coal_Vec3 vert2, float* t, float* u,
                                 float* v);
Coal_Vec3 coal_Lerp_Vec3(Coal_Vec3 a, Coal_Vec3 b, float t);
float     coal_Rand(void);
float     coal_RandRange(float min, float max);
Coal_Vec3 coal_RandCoal_Vec3(float min, float max);

#endif /* end of include guard: M_MATH_H */
