#include <coal/coal.h>

int main(int argc, char *argv[])
{
    Vec3 a = {.x[0] = 1, .x[1] = 0, .x[2] = 0};
    Vec3 b = {.x[0] = 1, .x[1] = 0, .x[2] = 0};
    Vec3 c = m_Add_Vec3(&a, &b);

    if (c.x[0] != 2)
        return 1;
    return 0;
}

