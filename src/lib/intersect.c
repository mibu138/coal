#ifndef COAL_SIMPLE_TYPE_NAMES
#define COAL_SIMPLE_TYPE_NAMES
#endif
#ifndef COAL_SIMPLE_FUNC_NAMES
#define COAL_SIMPLE_FUNC_NAMES
#endif
#include "intersect.h"
#include "linalg.h"

static bool raySegmentIntersect(Ray ray, Segment segment)
{
    const Vec2 v1 = sub_Vec2(ray.orig, segment.A);
    const Vec2 d1 = ray.dir;
    const Vec2 d2 = sub_Vec2(segment.B, segment.A);
    const Mat2 m1 = {
        v1.x, d2.x,
        v1.y, d2.y
    };
    const Mat2 m2 = {
        v1.x, d1.x,
        v1.y, d1.y
    };
    const Mat2 m3 = {
        d2.x, d1.x,
        d2.y, d1.y
    };
    const float denom = determinant(m3);
    if (denom == 0) return false;
    const float t1 = determinant(m1) / denom;
    const float t2 = determinant(m2) / denom;
    if (t1 < 0) return false;
    if (t2 < 0 || t2 > 1) return false;
    return true;
}

static bool segmentIntersect(Segment seg1, Segment seg2)
{
    const Vec2 v1 = sub_Vec2(seg1.A, seg2.A);
    const Vec2 d1 = sub_Vec2(seg1.B, seg1.A);
    const Vec2 d2 = sub_Vec2(seg2.B, seg2.A);
    const Mat2 m1 = {
        v1.x, d2.x,
        v1.y, d2.y
    };
    const Mat2 m2 = {
        v1.x, d1.x,
        v1.y, d1.y
    };
    const Mat2 m3 = {
        d2.x, d1.x,
        d2.y, d1.y
    };
    const float denom = determinant(m3);
    if (denom == 0) return false;
    const float t1 = determinant(m1) / denom;
    const float t2 = determinant(m2) / denom;
    if (t1 < 0 || t1 > 1) return false;
    if (t2 < 0 || t2 > 1) return false;
    return true;
}

static bool pointInCircle(Vec2 point, Vec2 center, const float radius)
{
    scale_Vec2(-1, center);
    translate_Vec2(center, point);
    return (length_Vec2(point) < radius * radius);
}

#define EPSILON 0.000001
// Moller & Trumbore triangle intersection algorithm
// this culls all triangles facing away
int coal_TriangleIntersect(const Vec3 orig, const Vec3 dir, 
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
