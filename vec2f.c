/**
 * File: vec2f.c
 * Author: Garrett Bates <gbates@cs.nmt.edu>
 * Description:
 * * Implementation for a 2-dimensional vector.
 */

#include <string.h>

#include "cgmath.h"

#if defined(CGMATH_VECTOR_DIMS_DEFINED)
#undef CGMATH_VECTOR_ELEMS
#undef CGMATH_VECTOR_SIZE
#undef CGMATH_VECTOR_DIMS_DEFINED
#endif

#define CGMATH_VECTOR_ELEMS     2
#define CGMATH_VECTOR_SIZE      (CGMATH_VECTOR_ELEMS * sizeof(float))
#define CGMATH_VECTOR_DIMS_DEFINED

void vec2f_zero(vec2f* vec)
{
        memset(vec->m, 0, CGMATH_VECTOR_SIZE);
}

void vec2f_identity(vec2f* vec, int axis)
{
        if(axis > 0 && axis < CGMATH_VECTOR_ELEMS) {
                vec2f_zero(vec);
                vec->m[axis] = 1.0f;
        }
}

void vec2f_add(vec2f* a, vec2f* b, vec2f* dest)
{
        vec2f tmp;
        memcpy(tmp.m, a->m, CGMATH_VECTOR_SIZE);

        tmp.m[VEC_X] += b->m[VEC_X];
        tmp.m[VEC_Y] += b->m[VEC_Y];

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

void vec2f_scale(vec2f* vec, float scalar, vec2f* dest)
{
        vec2f tmp;
        memcpy(tmp.m, vec->m, CGMATH_VECTOR_SIZE);

        tmp.m[VEC_X] *= scalar;
        tmp.m[VEC_Y] *= scalar;

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

float vec2f_scalar_prod(vec2f* a, vec2f* b)
{
        float sp;
        sp =    a->m[VEC_X] * b->m[VEC_X] +
                a->m[VEC_Y] * b->m[VEC_Y];
        return sp;
}

float vec2f_sqr_mag(vec2f* vec)
{
        return vec2f_scalar_prod(vec, vec);
}

void vec2f_normalize(vec2f* vec, vec2f* dest)
{
        long i;
        float x;
        float x2;
        vec2f tmp;

        memcpy(tmp.m, vec->m, CGMATH_VECTOR_SIZE);

        x = vec2f_sqr_mag(vec);
        x2 = 0.5 * x;
        i = *(long*)&x;
        i = 0x5f3759df - (i >> 1);
        x = *(float*)&i;
        x = x * (1.5f - x2 * x * x);

        tmp.m[VEC_X] = tmp.m[VEC_X] * x;
        tmp.m[VEC_Y] = tmp.m[VEC_Y] * x;

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

