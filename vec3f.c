/**
 * File: vec3f.c
 * Author: Garrett Bates <garrett.bates@cs.nmt.edu>
 * Description:
 * * Implementation for a 3-dimensional vector.
 */
#include <string.h>

#include "cgmath.h"

#if defined(CGMATH_VECTOR_DIMS_DEFINED)
#undef CGMATH_VECTOR_ELEMS
#undef CGMATH_VECTOR_SIZE
#undef CGMATH_VECTOR_DIMS_DEFINED
#endif

#define CGMATH_VECTOR_ELEMS     3
#define CGMATH_VECTOR_SIZE      (CGMATH_VECTOR_ELEMS * sizeof(float))
#define CGMATH_VECTOR_DIMS_DEFINED

void vec3f_zero(vec3f* vec)
{
        memset(vec->m, 0, CGMATH_VECTOR_SIZE);
}

void vec3f_identity(vec3f* vec, int axis)
{
        if(axis > 0 && axis < CGMATH_VECTOR_ELEMS) {
                vec3f_zero(vec);
                vec->m[axis] = 1.0f;
        }
}

void vec3f_add(vec3f* a, vec3f* b, vec3f* dest)
{
        vec3f tmp;
        memcpy(tmp.m, a->m, CGMATH_VECTOR_SIZE);

        tmp.m[VEC_X] += b->m[VEC_X];
        tmp.m[VEC_Y] += b->m[VEC_Y];
        tmp.m[VEC_Z] += b->m[VEC_Z];

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

void vec3f_scale(vec3f* vec, float scalar, vec3f* dest)
{
        vec3f tmp;
        memcpy(tmp.m, vec->m, CGMATH_VECTOR_SIZE);

        tmp.m[VEC_X] *= scalar;
        tmp.m[VEC_Y] *= scalar;
        tmp.m[VEC_Z] *= scalar;

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

float vec3f_scalar_prod(vec3f* a, vec3f* b)
{
        float sp;
        sp =    a->m[VEC_X] * b->m[VEC_X] +
                a->m[VEC_Y] * b->m[VEC_Y] +
                a->m[VEC_Z] * b->m[VEC_Z];
        return sp;
}

void vec3f_vector_prod(vec3f* a, vec3f* b, vec3f* dest)
{
        vec3f tmp;

        tmp.m[VEC_X] = a->m[VEC_Y] * b->m[VEC_Z] - a->m[VEC_Z] * b->m[VEC_Y];
        tmp.m[VEC_Y] = a->m[VEC_X] * b->m[VEC_Z] - a->m[VEC_Z] * b->m[VEC_X];
        tmp.m[VEC_Z] = a->m[VEC_X] * b->m[VEC_Y] - a->m[VEC_Y] * b->m[VEC_X];

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

float vec3f_sqr_mag(vec3f* vec)
{
        return vec3f_scalar_prod(vec, vec);
}

/**
 * All credit for the fast inverse square root
 * algorithm used here goes to whoever the hell
 * wrote it to begin with. Here's a neat article
 * discussing the history on beyond3d:
 * https://www.beyond3d.com/content/articles/8/
 */
void vec3f_normalize(vec3f* vec, vec3f* dest)
{
        long i;
        float x;
        vec3f tmp;

        memcpy(tmp.m, vec->m, CGMATH_VECTOR_SIZE);

        x = vec3f_sqr_mag(vec);

        x = _cgmath_invsqrt(x);

        tmp.m[VEC_X] = tmp.m[VEC_X] * x;
        tmp.m[VEC_Y] = tmp.m[VEC_Y] * x;
        tmp.m[VEC_Z] = tmp.m[VEC_Z] * x;

        memcpy(dest->m, tmp.m, CGMATH_VECTOR_SIZE);
}

