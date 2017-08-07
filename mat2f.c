/**
 * File: mat2f.c
 * Author: Garrett Bates <gbates@cs.nmt.edu>
 * Description:
 * * Implementation for a 2x2 matrix.
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

#define CGMATH_MATRIX_WIDTH     2
#define CGMATH_MATRIX_HEIGHT    2
#define CGMATH_MATRIX_ELEMS     (CGMATH_MATRIX_WIDTH * CGMATH_MATRIX_HEIGHT)
#define CGMATH_MATRIX_SIZE      (CGMATH_MATRIX_ELEMS * sizeof(float))
#define CGMATH_MATRIX_DIMS_DEFINED

void mat2f_zero(mat2f* mat)
{
        memset(mat->m, 0, CGMATH_MATRIX_SIZE);
}

void mat2f_identity(mat2f* mat)
{
        mat2f_zero(mat);
        mat->m[0][0] = 1.0f;
        mat->m[1][1] = 1.0f;
}

void mat2f_add(mat2f* a, mat2f* b, mat2f* dest)
{
        mat2f tmp;
        memcpy(tmp.m, a->m, CGMATH_MATRIX_SIZE);

        tmp.m[0][0] += b->m[0][0];
        tmp.m[0][1] += b->m[0][1];
        tmp.m[1][0] += b->m[1][0];
        tmp.m[1][1] += b->m[1][1];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat2f_scale(mat2f* mat, float scalar, mat2f* dest)
{
        mat2f tmp;
        memcpy(tmp.m, mat->m, CGMATH_MATRIX_SIZE);

        tmp.m[0][0] *= scalar;
        tmp.m[0][1] *= scalar;
        tmp.m[1][0] *= scalar;
        tmp.m[1][1] *= scalar;

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat2f_multiply(mat2f* a, mat2f* b, mat2f* dest)
{
        int i;
        int j;
        vec2f row;
        vec2f col;
        mat2f tmp;

        /*for(i = 0; i < CGMATH_MATRIX_HEIGHT; i++) {
                for(j = 0; j < CGMATH_MATRIX_WIDTH; j++) {
                        mat2f_get_row(a, &row, i);
                        mat2f_get_col(b, &col, j);
                        tmp.m[i][j] = vec2f_scalar_prod(&row, &col);
                }
        }*/

        tmp.m[0][0] =   a->m[0][0] * b->m[0][0] +
                        a->m[0][1] * b->m[1][0];
        tmp.m[0][1] =   a->m[0][0] * b->m[0][1] +
                        a->m[0][1] * b->m[1][1];
        tmp.m[1][0] =   a->m[1][0] * b->m[0][0] +
                        a->m[1][1] * b->m[1][0];
        tmp.m[1][1] =   a->m[1][0] * b->m[0][1] +
                        a->m[1][1] * b->m[1][1];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

float mat2f_determinant(mat2f* mat)
{
        float dt;
        dt = mat->m[0][0] * mat->m[1][1] - mat->m[0][1] * mat->m[1][0];
        return dt;
}

void mat2f_transpose(mat2f* mat, mat2f* dest)
{
        int i;
        int j;
        mat2f tmp;
        memcpy(tmp.m, mat->m, CGMATH_MATRIX_SIZE);

        *(int*)&tmp.m[0][1] ^= *(int*)&tmp.m[1][0];
        *(int*)&tmp.m[1][0] ^= *(int*)&tmp.m[0][1];
        *(int*)&tmp.m[0][1] ^= *(int*)&tmp.m[1][0];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat2f_inverse(mat2f* mat, mat2f* dest)
{
        float dt;
        mat2f tmp;
        
        dt = mat2f_determinant(mat);

        if(_cgmath_absf(dt) != 0.0f != 0.0f) {
                tmp.m[0][0] = mat->m[1][1];
                tmp.m[1][1] = mat->m[0][0];
                tmp.m[0][1] = -1.0f * mat->m[0][1];
                tmp.m[1][0] = -1.0f * mat->m[1][0];

                mat2f_scale(&tmp, 1.0f / dt, &tmp);
                memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
        }
}

void mat2f_get_row(mat2f* mat, vec2f* dest, int row)
{
        if(row > 0 && row < CGMATH_MATRIX_HEIGHT) {
                dest->m[0] = mat->m[row][0];
                dest->m[1] = mat->m[row][1];
        }
}

void mat2f_get_col(mat2f* mat, vec2f* dest, int col)
{
        if(col > 0 && col < CGMATH_MATRIX_WIDTH) {
                dest->m[0] = mat->m[0][col];
                dest->m[1] = mat->m[1][col];
        }
}

void mat2f_set_row(mat2f* mat, vec2f* src, int row)
{
        if(row > 0 && row < CGMATH_MATRIX_HEIGHT) {
                mat->m[row][0] = src->m[0];
                mat->m[row][1] = src->m[1];
        }
}

void mat2f_set_col(mat2f* mat, vec2f* src, int col)
{
        if(col > 0 && col < CGMATH_MATRIX_WIDTH) {
                mat->m[0][col] = src->m[0];
                mat->m[1][col] = src->m[1];
        }
}

