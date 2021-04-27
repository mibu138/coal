#include "stdio.h"
#include "coal.h"
#include "m.h"

int main(void)
{
    printf("Coal init.\n");
    Coal_Vec3 v = {coal_Rand(), coal_Rand(), coal_Rand()};
    printf("v: [%f, %f, %f]\n", v[0], v[1], v[2]);
    return 0;
}
