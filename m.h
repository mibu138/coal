#ifndef DEV_COAL_MATH_H
#define DEV_COAL_MATH_H

#ifndef __cplusplus
#define COAL_VEC3_IN  const float[static restrict 3] 
#define COAL_VEC3_OUT       float[static restrict 3] 
#define COAL_MAT4_IN  const float[static restrict 4][4]
#define COAL_MAT4_OUT       float[static restrict 4][4]
#else
#define COAL_VEC3_IN const float[3] 
#define COAL_VEC3_OUT      float[3] 
#define COAL_MAT4_IN const float[4][4]
#define COAL_MAT4_OUT      float[4][4]
#endif

void coal_Mat4_Identity(COAL_MAT4_OUT);
void coal_Mult_Mat4(COAL_MAT4_IN, COAL_MAT4_IN, COAL_MAT4_OUT);
void coal_Translate_Mat4(COAL_VEC3_IN, COAL_MAT4_IN, COAL_MAT4_OUT);
void coal_Copy_Mat4(COAL_MAT4_IN, COAL_MAT4_OUT);
void coal_Copy_Vec3(COAL_VEC3_IN, COAL_VEC3_OUT);

typedef float Coal_Vec3[3];
typedef float Coal_Mat4[4][4];
#define COAL_MAT4_IDENT {1, 0, 0, 0, \
                         0, 1, 0, 0, \
                         0, 0, 1, 0, \
                         0, 0, 0, 1}

#define COAL_MAT4_SIZE sizeof(Coal_Mat4)

#endif /* end of include guard: DEV_COAL_MATH_H */
