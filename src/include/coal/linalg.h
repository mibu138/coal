#ifndef COAL_LINALG_H
#define COAL_LINALG_H

#include "types.h"

#define COAL_MAT4_IDENT (Coal_Mat4){\
    1, 0, 0, 0, \
    0, 1, 0, 0, \
    0, 0, 1, 0, \
    0, 0, 0, 1  \
}

// START FUNCDECLS
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
Coal_Vec2 coal_Scale_Vec2(float scale, Coal_Vec2);
Coal_Vec2 coal_Add(Coal_Vec2, Coal_Vec2);
Coal_Vec2 coal_Add_Vec2(Coal_Vec2, Coal_Vec2); //calls coal_Add
float     coal_Distance(Coal_Vec2 a, Coal_Vec2 b);
float     coal_Dot(Coal_Vec3 a, Coal_Vec3 b);
Coal_Vec2 coal_Subtract(Coal_Vec2, Coal_Vec2); 
Coal_Vec2 coal_Sub_Vec2(Coal_Vec2, Coal_Vec2); //calls coal_Subtract
// returns a random float between 0 and 1
float     coal_Rand(void);
// returns a random float between -1 and 1
float     coal_RandNeg(void);
float     coal_Length_Vec2(Coal_Vec2);
float     coal_Length2_Vec2(Coal_Vec2);
float     coal_Determinant_Mat2(Coal_Mat2);
Coal_Vec2 coal_PolarToCart(float angle, float radius);
Coal_Mat4 coal_Invert4x4(Coal_Mat4);
Coal_Vec3 coal_Lerp_Vec3(Coal_Vec3 a, Coal_Vec3 b, float t);
float     coal_Rand(void);
float     coal_RandRange(float min, float max);
Coal_Vec3 coal_Rand_Vec3(float min, float max);
// END FUNCDECLS

#ifdef COAL_SIMPLE_FUNC_NAMES
#define ident_Mat4() coal_Ident_Mat4()
#define buildPerspective(p0, p1) coal_BuildPerspective(p0, p1)
#define getLocalX_Mat4(p0) coal_GetLocalX_Mat4(p0)
#define getLocalY_Mat4(p0) coal_GetLocalY_Mat4(p0)
#define getLocalZ_Mat4(p0) coal_GetLocalZ_Mat4(p0)
#define getTranslation_Mat4(p0) coal_GetTranslation_Mat4(p0)
#define add_Vec3(p0, p1) coal_Add_Vec3(p0, p1)
#define sub_Vec3(p0, p1) coal_Sub_Vec3(p0, p1)
#define normalize_Vec3(p0) coal_Normalize_Vec3(p0)
#define normalize_Vec4(p0) coal_Normalize_Vec4(p0)
#define scale_Vec3(p0, p1) coal_Scale_Vec3(p0, p1)
#define cross(p0, p1) coal_Cross(p0, p1)
#define lookAt(p0, p1, p2) coal_LookAt(p0, p1, p2)
#define lookAtInverse(p0, p1, p2, p3, p4) coal_LookAtInverse(p0, p1, p2, p3, p4)
#define rotate_Vec2(p0, p1) coal_Rotate_Vec2(p0, p1)
#define rotateY_Mat4(p0, p1) coal_RotateY_Mat4(p0, p1)
#define buildFromBasis_Mat4(p0, p1, p2) coal_BuildFromBasis_Mat4(p0, p1, p2)
#define buildRotate(p0, p1) coal_BuildRotate(p0, p1)
#define rotateY_Vec3(p0, p1) coal_RotateY_Vec3(p0, p1)
#define rotateZ_Mat4(p0, p1) coal_RotateZ_Mat4(p0, p1)
#define mult_Mat4(p0, p1) coal_Mult_Mat4(p0, p1)
#define mult_Mat4Vec3(p0, p1) coal_Mult_Mat4Vec3(p0, p1)
#define mult_Mat4Vec4(p0, p1) coal_Mult_Mat4Vec4(p0, p1)
#define translate_Mat4(p0, p1) coal_Translate_Mat4(p0, p1)
#define transpose_Mat4(p0) coal_Transpose_Mat4(p0)
#define scaleUniform_Mat4(p0, p1) coal_ScaleUniform_Mat4(p0, p1)
#define scaleNonUniform_Mat4(p0, p1) coal_ScaleNonUniform_Mat4(p0, p1)
#define translate_Vec2(p0, p1) coal_Translate_Vec2(p0, p1)
#define scale_Vec2(p0, p1) coal_Scale_Vec2(p0, p1)
#define add(p0, p1) coal_Add(p0, p1)
#define add_Vec2(p0, p1) coal_Add_Vec2(p0, p1)
#define distance(p0, p1) coal_Distance(p0, p1)
#define dot(p0, p1) coal_Dot(p0, p1)
#define subtract(p0, p1) coal_Subtract(p0, p1)
#define sub_Vec2(p0, p1) coal_Sub_Vec2(p0, p1)
#define rand() coal_Rand()
#define randNeg() coal_RandNeg()
#define length_Vec2(p0) coal_Length_Vec2(p0)
#define length2_Vec2(p0) coal_Length2_Vec2(p0)
#define determinant(p0) coal_Determinant_Mat2(p0)
#define polarToCart(p0, p1) coal_PolarToCart(p0, p1)
#define invert4x4(p0) coal_Invert4x4(p0)
#define lerp_Vec3(p0, p1, p2) coal_Lerp_Vec3(p0, p1, p2)
#define rand() coal_Rand()
#define randRange(p0, p1) coal_RandRange(p0, p1)
#define rand_Vec3(p0, p1) coal_Rand_Vec3(p0, p1)
#endif

#endif /* end of include guard: M_MATH_H */
