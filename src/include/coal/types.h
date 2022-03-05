#ifndef COAL_TYPES_H
#define COAL_TYPES_H

#ifdef COAL_64_BIT_REAL
typedef double real;
#else
typedef float real;
#endif

typedef union Coal_Vec2 {
    real e[2];
    struct {
        real x;
        real y;
    };
    struct {
        real width;
        real height;
    };
#ifdef __cplusplus
    Coal_Vec2
    operator+(const Coal_Vec2& v) const
    {
        return {this->x + v.x, this->y + v.y};
    }

    Coal_Vec2&
    operator+=(const Coal_Vec2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Coal_Vec2&
    operator-=(const Coal_Vec2& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Coal_Vec2
    operator-(const Coal_Vec2& v) const
    {
        return {this->x - v.x, this->y - v.y};
    }

    Coal_Vec2
    operator*(const real s) const
    {
        return {this->x * s, this->y * s};
    }
#endif
} Coal_Vec2;

typedef union Coal_Vec3 {
    real e[3];
    struct {
        real x;
        real y;
        real z;
    };
    struct {
        real r;
        real g;
        real b;
    };
} Coal_Vec3;

typedef union Coal_Vec4 {
    real e[4];
    struct {
        real x;
        real y;
        real z;
        real w;
    };
    struct {
        real r;
        real g;
        real b;
        real a;
    };
    struct {
        real offsetx;
        real offsety;
        real width;
        real height;
    };
} Coal_Vec4;

typedef struct Coal_Mat2 {
    real x00, x01, x10, x11;
} Coal_Mat2;

typedef struct Coal_Mat3 {
    real e[3][3];
} Coal_Mat3;

typedef struct Coal_Mat4 {
    real e[4][4];
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
