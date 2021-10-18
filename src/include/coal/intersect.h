#include "types.h"
#include <stdbool.h>

bool coal_RaySegmentIntersect(Coal_Ray ray, Coal_Segment segment);
bool coal_SegmentIntersect(Coal_Segment seg1, Coal_Segment seg2);
bool coal_PointInCircle(Coal_Vec2 point, Coal_Vec2 center, const float radius);
int  coal_TriangleIntersect(Coal_Vec3 orig, Coal_Vec3 dir, Coal_Vec3 vert0,
                            Coal_Vec3 vert1, Coal_Vec3 vert2, float* t, float* u,
                            float* v);
bool coal_AABBIntersect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
bool coal_PointInBox(float x, float y, float bx, float by, float bw, float bh);
