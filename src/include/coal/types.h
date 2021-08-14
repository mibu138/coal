#ifndef COAL_TYPES_H
#define COAL_TYPES_H

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

#ifdef COAL_SIMPLE_TYPE_NAMES
typedef Coal_Vec2    Vec2;
typedef Coal_Vec3    Vec3;
typedef Coal_Vec4    Vec4;
typedef Coal_Mat2    Mat2;
typedef Coal_Mat3    Mat3;
typedef Coal_Mat4    Mat4;
typedef Coal_Ray     Ray;
typedef Coal_Segment Segment;
#endif

#endif
