#include "types.h"
#include <stdbool.h>

bool coal_RaySegmentIntersect(Coal_Ray ray, Coal_Segment segment);
bool coal_SegmentIntersect(Coal_Segment seg1, Coal_Segment seg2);
bool coal_PointInCircle(Coal_Vec2 point, Coal_Vec2 center, const real radius);
int  coal_TriangleIntersect(Coal_Vec3 orig, Coal_Vec3 dir, Coal_Vec3 vert0,
                            Coal_Vec3 vert1, Coal_Vec3 vert2, real* t, real* u,
                            real* v);
bool coal_AABBIntersect(real x1, real y1, real w1, real h1, real x2, real y2, real w2, real h2);
bool coal_PointInBox(real x, real y, real bx, real by, real bw, real bh);
