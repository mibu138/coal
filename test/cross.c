#include "coal/util.h"
#include "coal/coal.h"

int main(int argc, char *argv[])
{
    Vec3 a = {1, 0, 0};
    Vec3 b = {1, 0, 0};
    Vec3 c = coal_Cross(a, b);

    coal_PrintVec3(c);

    if (c.x != 0)
        return 1;
    return 0;
}

