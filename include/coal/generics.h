#ifndef COAL_GENERICS_H
#define COAL_GENERICS_H
#include "coal.h"

#define coal_ident(a) _Generic((a), \
            Coal_Mat2: coal_ident_mat2) ()

#define coal_mul(a, b) _Generic((a), \
            Coal_Mat2: _Generic((b), \
               Coal_Vec2: coal_Mult_Mat2Vec2, \
               Coal_Mat2: coal_Mult_Mat2, \
               float: coal_Scale_Mat2, \
               double: coal_Scale_Mat2)) (a, b)
#define coal_rot(a, b) \
            _Generic((a), \
                float: _Generic((b), \
                    Coal_Mat2: coal_Rotate_Mat2), \
                double: _Generic((b), \
                    Coal_Mat2: coal_Rotate_Mat2) \
            ) (a, b)
#define coal_print(a) _Generic((a), \
            Coal_Mat2: coal_PrintMat2) (a)
#ifdef COAL_SIMPLE_FUNC_NAMES
#define mul(...) coal_mul(__VA_ARGS__)
#define ident(a) coal_ident(a)
#define rot(a, b) coal_rot(a, b)
#endif
#endif
