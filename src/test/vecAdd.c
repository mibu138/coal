#include "linalg.h"

int main(int argc, char *argv[])
{
    Vec3 a = {1, 0, 0};
    Vec3 b = {1, 0, 0};
    Vec3 c = coal_Add_Vec3(a, b);

    if (c.x != 2)
        return 1;
    return 0;
}

