#include <stdio.h>
#include "cgmath.h"

int main(int argc, char* argv[])
{
        int i;
        mat3f m1 =      {{{1.0f, 2.0f, 3.0f},
                        {2.0f, 2.0f, 3.0f},
                        {3.0f, 3.0f, 3.0f}}};
        mat3f m2;

        mat3f_inverse(&m1, &m2);

        for(i = 0; i < 3; i++) {
                printf("%f, %f, %f\n", m1.m[i][0], m1.m[i][1], m1.m[i][2]);
        }

        for(i = 0; i < 3; i++) {
                printf("%f, %f, %f\n", m2.m[i][0], m2.m[i][1], m2.m[i][2]);
        }

        return 0;
}

