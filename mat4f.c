/**
 * File: mat4f.c
 * Author: Garrett Bates <gbates@cs.nmt.edu>
 * Description:
 * * Implementation for a 4x4 matrix.
 */

#include <string.h>

#include "cgmath.h"

#if defined(CGMATH_MATRIX_DIMS_DEFINED)
#undef CGMATH_MATRIX_WIDTH
#undef CGMATH_MATRIX_HEIGHT
#undef CGMATH_MATRIX_ELEMS
#undef CGMATH_MATRIX_SIZE
#undef CGMATH_MATRIX_DIMS_DEFINED
#endif

#define CGMATH_MATRIX_WIDTH     4
#define CGMATH_MATRIX_HEIGHT    4
#define CGMATH_MATRIX_ELEMS     (CGMATH_MATRIX_WIDTH * CGMATH_MATRIX_HEIGHT)
#define CGMATH_MATRIX_SIZE      (CGMATH_MATRIX_ELEMS * sizeof(float))
#define CGMATH_MATRIX_DIMS_DEFINED

void mat4f_zero(mat4f* mat)
{
        memset(mat->m, 0, CGMATH_MATRIX_SIZE);
}

void mat4f_identity(mat4f* mat)
{
        mat4f_zero(mat);
        mat->m[0][0] = 1.0f;
        mat->m[1][1] = 1.0f;
        mat->m[2][2] = 1.0f;
        mat->m[3][3] = 1.0f;
}

void mat4f_add(mat4f* a, mat4f* b, mat4f* dest)
{
        mat4f tmp;
        memcpy(tmp.m, a->m, CGMATH_MATRIX_SIZE);

        tmp.m[0][0] += b->m[0][0];
        tmp.m[0][1] += b->m[0][1];
        tmp.m[0][2] += b->m[0][2];
        tmp.m[0][3] += b->m[0][3];
        tmp.m[1][0] += b->m[1][0];
        tmp.m[1][1] += b->m[1][1];
        tmp.m[1][2] += b->m[1][2];
        tmp.m[1][3] += b->m[1][3];
        tmp.m[2][0] += b->m[2][0];
        tmp.m[2][1] += b->m[2][1];
        tmp.m[2][2] += b->m[2][2];
        tmp.m[2][3] += b->m[2][3];
        tmp.m[3][0] += b->m[3][0];
        tmp.m[3][1] += b->m[3][1];
        tmp.m[3][2] += b->m[3][2];
        tmp.m[3][3] += b->m[3][3];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat4f_scale(mat4f* mat, float scalar, mat4f* dest)
{
        mat4f tmp;
        memcpy(tmp.m, mat->m, CGMATH_MATRIX_SIZE);

        tmp.m[0][0] *= scalar;
        tmp.m[0][1] *= scalar;
        tmp.m[0][2] *= scalar;
        tmp.m[0][3] *= scalar;
        tmp.m[1][0] *= scalar;
        tmp.m[1][1] *= scalar;
        tmp.m[1][2] *= scalar;
        tmp.m[1][3] *= scalar;
        tmp.m[2][0] *= scalar;
        tmp.m[2][1] *= scalar;
        tmp.m[2][2] *= scalar;
        tmp.m[2][3] *= scalar;
        tmp.m[0][3] *= scalar;
        tmp.m[1][3] *= scalar;
        tmp.m[2][3] *= scalar;
        tmp.m[3][3] *= scalar;

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat4f_multiply(mat4f* a, mat4f* b, mat4f* dest)
{
        int i;
        int j;
        vec4f row;
        vec4f col;
        mat4f tmp;

        tmp.m[0][0] =   a->m[0][0] * b->m[0][0] +
                        a->m[0][1] * b->m[1][0] +
                        a->m[0][2] * b->m[2][0] +
                        a->m[0][3] * b->m[3][0];
        tmp.m[0][1] =   a->m[0][0] * b->m[0][1] +
                        a->m[0][1] * b->m[1][1] +
                        a->m[0][2] * b->m[2][1] +
                        a->m[0][3] * b->m[3][1];
        tmp.m[0][2] =   a->m[0][0] * b->m[0][2] +
                        a->m[0][1] * b->m[1][2] +
                        a->m[0][2] * b->m[2][2] +
                        a->m[0][3] * b->m[3][2];
        tmp.m[0][3] =   a->m[0][0] * b->m[0][3] +
                        a->m[0][1] * b->m[1][3] +
                        a->m[0][2] * b->m[2][3] +
                        a->m[0][3] * b->m[3][3];
        tmp.m[1][0] =   a->m[1][0] * b->m[0][0] +
                        a->m[1][1] * b->m[1][0] +
                        a->m[1][2] * b->m[2][0] +
                        a->m[1][3] * b->m[3][0];
        tmp.m[1][1] =   a->m[1][0] * b->m[0][1] +
                        a->m[1][1] * b->m[1][1] +
                        a->m[1][2] * b->m[2][1] +
                        a->m[1][3] * b->m[3][1];
        tmp.m[1][2] =   a->m[1][0] * b->m[0][2] +
                        a->m[1][1] * b->m[1][2] +
                        a->m[1][2] * b->m[2][2] +
                        a->m[1][3] * b->m[3][2];
        tmp.m[1][3] =   a->m[1][0] * b->m[0][3] +
                        a->m[1][1] * b->m[1][3] +
                        a->m[1][2] * b->m[2][3] +
                        a->m[1][3] * b->m[3][3];
        tmp.m[2][0] =   a->m[2][0] * b->m[0][0] +
                        a->m[2][1] * b->m[1][0] +
                        a->m[2][2] * b->m[2][0] +
                        a->m[2][3] * b->m[3][0];
        tmp.m[2][1] =   a->m[2][0] * b->m[0][1] +
                        a->m[2][1] * b->m[1][1] +
                        a->m[2][2] * b->m[2][1] +
                        a->m[2][3] * b->m[3][1];
        tmp.m[2][2] =   a->m[2][0] * b->m[0][2] +
                        a->m[2][1] * b->m[1][2] +
                        a->m[2][2] * b->m[2][2] +
                        a->m[2][3] * b->m[3][2];
        tmp.m[2][3] =   a->m[2][0] * b->m[0][3] +
                        a->m[2][1] * b->m[1][3] +
                        a->m[2][2] * b->m[2][3] +
                        a->m[2][3] * b->m[3][3];
        tmp.m[3][0] =   a->m[3][0] * b->m[0][0] +
                        a->m[3][1] * b->m[1][0] +
                        a->m[3][2] * b->m[2][0] +
                        a->m[3][3] * b->m[3][0];
        tmp.m[3][1] =   a->m[3][0] * b->m[0][1] +
                        a->m[3][1] * b->m[1][1] +
                        a->m[3][2] * b->m[2][1] +
                        a->m[3][3] * b->m[3][1];
        tmp.m[3][2] =   a->m[3][0] * b->m[0][2] +
                        a->m[3][1] * b->m[1][2] +
                        a->m[3][2] * b->m[2][2] +
                        a->m[3][3] * b->m[3][2];
        tmp.m[3][3] =   a->m[3][0] * b->m[0][3] +
                        a->m[3][1] * b->m[1][3] +
                        a->m[3][2] * b->m[2][3] +
                        a->m[3][3] * b->m[3][3];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

/**
 * How many layers of determinants are you on?
 * You are like a baby. Watch this.
 */
float mat4f_determinant(mat4f* mat)
{
        float dt;
        mat3f sm;

        dt = 0.0f;

        sm.m[0][0] = mat->m[1][1];
        sm.m[0][1] = mat->m[1][2];
        sm.m[0][2] = mat->m[1][3];
        sm.m[1][0] = mat->m[2][1];
        sm.m[1][1] = mat->m[2][2];
        sm.m[1][2] = mat->m[2][3];
        sm.m[2][0] = mat->m[3][1];
        sm.m[2][1] = mat->m[3][2];
        sm.m[2][2] = mat->m[3][3];
        dt += mat->m[0][0] * mat3f_determinant(&sm);

        sm.m[0][0] = mat->m[1][0];
        sm.m[0][1] = mat->m[1][2];
        sm.m[0][2] = mat->m[1][3];
        sm.m[1][0] = mat->m[2][0];
        sm.m[1][1] = mat->m[2][2];
        sm.m[1][2] = mat->m[2][3];
        sm.m[2][0] = mat->m[3][0];
        sm.m[2][1] = mat->m[3][2];
        sm.m[2][2] = mat->m[3][3];
        dt -= mat->m[0][1] * mat3f_determinant(&sm);

        sm.m[0][0] = mat->m[1][0];
        sm.m[0][1] = mat->m[1][1];
        sm.m[0][2] = mat->m[1][3];
        sm.m[1][0] = mat->m[2][0];
        sm.m[1][1] = mat->m[2][1];
        sm.m[1][2] = mat->m[2][3];
        sm.m[2][0] = mat->m[3][0];
        sm.m[2][1] = mat->m[3][1];
        sm.m[2][2] = mat->m[3][3];
        dt += mat->m[0][2] * mat3f_determinant(&sm);

        sm.m[0][0] = mat->m[1][0];
        sm.m[0][1] = mat->m[1][1];
        sm.m[0][2] = mat->m[1][2];
        sm.m[1][0] = mat->m[2][0];
        sm.m[1][1] = mat->m[2][1];
        sm.m[1][2] = mat->m[2][2];
        sm.m[2][0] = mat->m[3][0];
        sm.m[2][1] = mat->m[3][1];
        sm.m[2][2] = mat->m[3][2];
        dt += mat->m[0][3] * mat3f_determinant(&sm);

        return dt;
}

void mat4f_transpose(mat4f* mat, mat4f* dest)
{
        int i;
        int j;
        mat4f tmp;
        memcpy(tmp.m, mat->m, CGMATH_MATRIX_SIZE);

        *(int*)&tmp.m[0][1] ^= *(int*)&tmp.m[1][0];
        *(int*)&tmp.m[1][0] ^= *(int*)&tmp.m[0][1];
        *(int*)&tmp.m[0][1] ^= *(int*)&tmp.m[1][0];

        *(int*)&tmp.m[0][2] ^= *(int*)&tmp.m[2][0];
        *(int*)&tmp.m[2][0] ^= *(int*)&tmp.m[0][2];
        *(int*)&tmp.m[0][2] ^= *(int*)&tmp.m[2][0];

        *(int*)&tmp.m[0][3] ^= *(int*)&tmp.m[3][0];
        *(int*)&tmp.m[3][0] ^= *(int*)&tmp.m[0][3];
        *(int*)&tmp.m[0][3] ^= *(int*)&tmp.m[3][0];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat4f_inverse(mat4f* mat, mat4f* dest)
{
        float dt;
        mat4f tmp;
        mat3f sm;

        dt = mat4f_determinant(mat);

        if(_cgmath_absf(dt) != 0.0f) {
                sm.m[0][0] = mat->m[1][1];
                sm.m[0][1] = mat->m[1][2];
                sm.m[0][2] = mat->m[1][3];
                sm.m[1][0] = mat->m[2][1];
                sm.m[1][1] = mat->m[2][2];
                sm.m[1][2] = mat->m[2][3];
                sm.m[2][0] = mat->m[3][1];
                sm.m[2][1] = mat->m[3][2];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[0][0] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[1][0];
                sm.m[0][1] = mat->m[1][2];
                sm.m[0][2] = mat->m[1][3];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][2];
                sm.m[1][2] = mat->m[2][3];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][2];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[0][1] = -1.0f * mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[1][0];
                sm.m[0][1] = mat->m[1][1];
                sm.m[0][2] = mat->m[1][3];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][1];
                sm.m[1][2] = mat->m[2][3];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][1];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[0][2] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[1][0];
                sm.m[0][1] = mat->m[1][1];
                sm.m[0][2] = mat->m[1][2];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][1];
                sm.m[1][2] = mat->m[2][2];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][1];
                sm.m[2][2] = mat->m[3][2];
                tmp.m[0][3] = -1.0f * mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][1];
                sm.m[0][1] = mat->m[0][2];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[2][1];
                sm.m[1][1] = mat->m[2][2];
                sm.m[1][2] = mat->m[2][3];
                sm.m[2][0] = mat->m[3][1];
                sm.m[2][1] = mat->m[3][2];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[1][0] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][2];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][2];
                sm.m[1][2] = mat->m[2][3];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][2];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[1][1] = -1.0f * mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][1];
                sm.m[1][2] = mat->m[2][3];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][1];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[1][2] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[0][2] = mat->m[0][2];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][1];
                sm.m[1][2] = mat->m[2][2];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][1];
                sm.m[2][2] = mat->m[3][2];
                tmp.m[1][3] = -1.0f * mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][1];
                sm.m[0][1] = mat->m[0][2];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[1][1];
                sm.m[1][1] = mat->m[1][2];
                sm.m[1][2] = mat->m[1][3];
                sm.m[2][0] = mat->m[3][1];
                sm.m[2][1] = mat->m[3][2];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[2][0] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][2];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][2];
                sm.m[1][2] = mat->m[1][3];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][2];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[2][1] = -1.0f * mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][1];
                sm.m[1][2] = mat->m[1][3];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][1];
                sm.m[2][2] = mat->m[3][3];
                tmp.m[2][2] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[0][2] = mat->m[0][2];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][1];
                sm.m[1][2] = mat->m[1][2];
                sm.m[2][0] = mat->m[3][0];
                sm.m[2][1] = mat->m[3][1];
                sm.m[2][2] = mat->m[3][2];
                tmp.m[2][3] = -1.0f * mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][1];
                sm.m[0][1] = mat->m[0][2];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[1][1];
                sm.m[1][1] = mat->m[1][2];
                sm.m[1][2] = mat->m[1][3];
                sm.m[2][0] = mat->m[2][1];
                sm.m[2][1] = mat->m[2][2];
                sm.m[2][2] = mat->m[2][3];
                tmp.m[3][0] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][2];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][2];
                sm.m[1][2] = mat->m[1][3];
                sm.m[2][0] = mat->m[2][0];
                sm.m[2][1] = mat->m[2][2];
                sm.m[2][2] = mat->m[2][3];
                tmp.m[3][1] = -1.0f * mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[0][2] = mat->m[0][3];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][1];
                sm.m[1][2] = mat->m[1][3];
                sm.m[2][0] = mat->m[2][0];
                sm.m[2][1] = mat->m[2][1];
                sm.m[2][2] = mat->m[2][3];
                tmp.m[3][2] = mat3f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[0][2] = mat->m[0][2];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][1];
                sm.m[1][2] = mat->m[1][2];
                sm.m[2][0] = mat->m[2][0];
                sm.m[2][1] = mat->m[2][1];
                sm.m[2][2] = mat->m[2][2];
                tmp.m[3][3] = -1.0f * mat3f_determinant(&sm);

                mat4f_transpose(&tmp, &tmp);
                mat4f_scale(&tmp, 1.0f/dt, &tmp);
                memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
        }
}

void mat4f_get_row(mat4f* mat, vec4f* dest, int row)
{
        if(row > 0 && row < CGMATH_MATRIX_HEIGHT) {
                dest->m[0] = mat->m[row][0];
                dest->m[1] = mat->m[row][1];
                dest->m[2] = mat->m[row][2];
                dest->m[3] = mat->m[row][3];
        }
}

void mat4f_get_col(mat4f* mat, vec4f* dest, int col)
{
        if(col > 0 && col < CGMATH_MATRIX_WIDTH) {
                dest->m[0] = mat->m[0][col];
                dest->m[1] = mat->m[1][col];
                dest->m[2] = mat->m[2][col];
                dest->m[3] = mat->m[3][col];
        }
}

void mat4f_set_row(mat4f* mat, vec4f* src, int row)
{
        if(row > 0 && row < CGMATH_MATRIX_HEIGHT) {
                mat->m[row][0] = src->m[0];
                mat->m[row][1] = src->m[1];
                mat->m[row][2] = src->m[2];
                mat->m[row][3] = src->m[3];
        }
}

void mat4f_set_col(mat4f* mat, vec4f* src, int col)
{
        if(col > 0 && col < CGMATH_MATRIX_WIDTH) {
                mat->m[0][col] = src->m[0];
                mat->m[1][col] = src->m[1];
                mat->m[2][col] = src->m[2];
                mat->m[3][col] = src->m[3];
        }
}

