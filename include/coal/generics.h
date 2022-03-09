#ifndef COAL_GENERICS_H
#define COAL_GENERICS_H

#include "linalg.h"
#include "types.h"

#define coal_notImplemented(...)                                               \
    do                                                                         \
    {                                                                          \
    } while (0)

#ifndef __cplusplus
#define coal_ident(a) _Generic((a), Coal_Mat2 : coal_ident_mat2)()

#define coal_add(a, b)                                                         \
    _Generic((a), Coal_Ivec2                                                   \
             : _Generic((b), Coal_Ivec2                                        \
                        : coal_Add_Ivec2, Coal_Vec2                            \
                        : coal_Add_Ivec2Vec2),                                 \
               Coal_Vec2                                                       \
             : _Generic((b), Coal_Vec2                                         \
                        : coal_Add_Vec2)),                                     \
        (a, b)

#define coal_mul(a, b)                                                         \
    _Generic((a), double                                                       \
             : _Generic((b), Coal_Vec2                                         \
                        : coal_Scale_Vec2, Coal_Ivec2                          \
                        : coal_Scale_Ivec2, Coal_Mat2                          \
                        : coal_Scale_Mat2),                                    \
               float                                                           \
             : _Generic((b), Coal_Vec2                                         \
                        : coal_Scale_Vec2, Coal_Ivec2                          \
                        : coal_Scale_Ivec2, Coal_Mat2                          \
                        : coal_Scale_Mat2),                                    \
               Coal_Mat2                                                       \
             : _Generic((b), Coal_Vec2                                         \
                        : coal_Mult_Mat2Vec2, Coal_Ivec2                       \
                        : coal_Mult_Mat2Vec2, Coal_Mat2                        \
                        : coal_Mult_Mat2))(a, b)

#define coal_rot(a, b)                                                         \
    _Generic((a), float                                                        \
             : _Generic((b), Coal_Mat2                                         \
                        : coal_Rotate_Mat2),                                   \
               double                                                          \
             : _Generic((b), Coal_Mat2                                         \
                        : coal_Rotate_Mat2))(a, b)

#define coal_floor(a) _Generic((a), Coal_Vec2 : coal_Floor_Vec2)(a)

#define coal_print(a) _Generic((a), Coal_Mat2 : coal_PrintMat2)(a)
#else
#define coal_ident(a) coal_notImplemented()
#define coal_mul(a, b) coal_notImplemented()
#define coal_rot(a, b) coal_notImplemented()
#define coal_print(a) coal_notImplemented()
#endif

#ifdef COAL_SIMPLE_FUNC_NAMES
#define add coal_add
#define mul coal_mul
#define ident coal_ident
#define rot coal_rot
#define floor coal_floor
#endif

#endif
