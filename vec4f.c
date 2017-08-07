/**
 * File: vec4f.c
 * Author: Garrett Bates <garrett.bates@cs.nmt.edu>
 * Description:
 * * Implementation for a 4-dimensional vector.
 */
#include <string.h>

#include "cgmath.h"

#if defined(CGMATH_VECTOR_DIMS_DEFINED)
#undef CGMATH_VECTOR_ELEMS
#undef CGMATH_VECTOR_SIZE
#undef CGMATH_VECTOR_DIMS_DEFINED
#endif

#define CGMATH_VECTOR_ELEMS     4
#define CGMATH_VECTOR_SIZE      (CGMATH_VECTOR_ELEMS * sizeof(float))
#define CGMATH_VECTOR_DIMS_DEFINED

void vec4f_zero(vec4f* vec)
{
        memset(vec->m, 0, CGMATH_VECTOR_SIZE);
}

void vec4f_identity(vec4f* vec, int axis)
{
        if(axis > 0 && axis < CGMATH_VECTOR_ELEMS) {
                vec4f_zero(vec);
                vec->m[axis] = 1.0f;
        }
}

void vec4f_add(vec4f* a, vec4f* b, vec4f* dest)
{
        vec4f tmp;
        memcpy(tmp.m, a->m, CGMATH_VECTOR_SIZE);

        tmp.m[VEC_X] += b->m[VEC_X];
        tmp.m[VEC_Y] += b->m[VEC_Y];
        tmp.m[VEC_Z] += b->m[VEC_Z];
        tmp.m[VEC_W] += b->m[VEC_W];

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

void vec4f_scale(vec4f* vec, float scalar, vec4f* dest)
{
        vec4f tmp;
        memcpy(tmp.m, vec->m, CGMATH_VECTOR_SIZE);

        tmp.m[VEC_X] *= scalar;
        tmp.m[VEC_Y] *= scalar;
        tmp.m[VEC_Z] *= scalar;
        tmp.m[VEC_W] *= scalar;

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

float vec4f_scalar_prod(vec4f* a, vec4f* b)
{
        float sp;
        sp =    a->m[VEC_X] * b->m[VEC_X] +
                a->m[VEC_Y] * b->m[VEC_Y] +
                a->m[VEC_Z] * b->m[VEC_Z] +
                a->m[VEC_W] * b->m[VEC_W];
        return sp;
}

float vec4f_sqr_mag(vec4f* vec)
{
        return vec4f_scalar_prod(vec, vec);
}

void vec4f_normalize(vec4f* vec, vec4f* dest)
{
        long i;
        float x;
        float x2;
        vec4f tmp;

        memcpy(tmp.m, vec->m, CGMATH_VECTOR_SIZE);

        x = vec4f_sqr_mag(vec);
        x2 = 0.5 * x;
        i = *(long*)&x;
        i = 0x5f3759df - (i >> 1);
        x = *(float*)&i;
        x = x * (1.5f - x2 * x * x);

        tmp.m[VEC_X] = tmp.m[VEC_X] * x;
        tmp.m[VEC_Y] = tmp.m[VEC_Y] * x;
        tmp.m[VEC_Z] = tmp.m[VEC_Z] * x;
        tmp.m[VEC_W] = tmp.m[VEC_W] * x;

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

