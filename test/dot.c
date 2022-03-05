#include "coal/linalg.h"

int main(int argc, char *argv[])
{
    Vec3 a = {1, 0, 0};
    Vec3 b = {1, 0, 0};
    float r = coal_Dot(a, b);
    if (r != 1)
        return 1;
    return 0;
}
