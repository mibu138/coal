#include <coal/coal.h>
#include <coal/generics.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    real theta = 2.0;
    Mat2 m = ident(m);
    coal_print(m);
    m = mul(0.2, m);
    coal_print(m);
    m = rot(PI / 4, m);
    coal_print(m);
    return 0;
}
