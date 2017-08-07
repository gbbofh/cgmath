/**
 * File: mat3f.c
 * Author: Garrett Bates <garrett.bates@cs.nmt.edu>
 * Description:
 * * Implementation for a 3x3 matrix.
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

#define CGMATH_MATRIX_WIDTH     3
#define CGMATH_MATRIX_HEIGHT    3
#define CGMATH_MATRIX_ELEMS     (CGMATH_MATRIX_WIDTH * CGMATH_MATRIX_HEIGHT)
#define CGMATH_MATRIX_SIZE      (CGMATH_MATRIX_ELEMS * sizeof(float))
#define CGMATH_MATRIX_DIMS_DEFINED

void mat3f_zero(mat3f* mat)
{
        memset(mat->m, 0, CGMATH_MATRIX_SIZE);
}

void mat3f_identity(mat3f* mat)
{
        mat3f_zero(mat);
        mat->m[0][0] = 1.0f;
        mat->m[1][1] = 1.0f;
        mat->m[2][2] = 1.0f;
}

void mat3f_add(mat3f* a, mat3f* b, mat3f* dest)
{
        mat3f tmp;
        memcpy(tmp.m, a->m, CGMATH_MATRIX_SIZE);

        tmp.m[0][0] += b->m[0][0];
        tmp.m[0][1] += b->m[0][1];
        tmp.m[0][2] += b->m[0][2];
        tmp.m[1][0] += b->m[1][0];
        tmp.m[1][1] += b->m[1][1];
        tmp.m[1][2] += b->m[1][2];
        tmp.m[2][0] += b->m[2][0];
        tmp.m[2][1] += b->m[2][1];
        tmp.m[2][2] += b->m[2][2];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat3f_scale(mat3f* mat, float scalar, mat3f* dest)
{
        mat3f tmp;
        memcpy(tmp.m, mat->m, CGMATH_MATRIX_SIZE);

        tmp.m[0][0] *= scalar;
        tmp.m[0][1] *= scalar;
        tmp.m[0][2] *= scalar;
        tmp.m[1][0] *= scalar;
        tmp.m[1][1] *= scalar;
        tmp.m[1][2] *= scalar;
        tmp.m[2][0] *= scalar;
        tmp.m[2][1] *= scalar;
        tmp.m[2][2] *= scalar;

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat3f_multiply(mat3f* a, mat3f* b, mat3f* dest)
{
        int i;
        int j;
        vec3f row;
        vec3f col;
        mat3f tmp;

        tmp.m[0][0] =   a->m[0][0] * b->m[0][0] +
                        a->m[0][1] * b->m[1][0] +
                        a->m[0][2] * b->m[2][0];
        tmp.m[0][1] =   a->m[0][0] * b->m[0][1] +
                        a->m[0][1] * b->m[1][1] +
                        a->m[0][2] * b->m[2][1];
        tmp.m[0][2] =   a->m[0][0] * b->m[0][2] +
                        a->m[0][1] * b->m[1][2] +
                        a->m[0][2] * b->m[2][2];
        tmp.m[1][0] =   a->m[1][0] * b->m[0][0] +
                        a->m[1][1] * b->m[1][0] +
                        a->m[1][2] * b->m[2][0];
        tmp.m[1][1] =   a->m[1][0] * b->m[0][1] +
                        a->m[1][1] * b->m[1][1] +
                        a->m[1][2] * b->m[2][1];
        tmp.m[1][2] =   a->m[1][0] * b->m[0][2] +
                        a->m[1][1] * b->m[1][2] +
                        a->m[1][2] * b->m[2][2];
        tmp.m[2][0] =   a->m[2][0] * b->m[0][0] +
                        a->m[2][1] * b->m[1][0] +
                        a->m[2][2] * b->m[2][0];
        tmp.m[2][1] =   a->m[2][0] * b->m[0][1] +
                        a->m[2][1] * b->m[1][1] +
                        a->m[2][2] * b->m[2][1];
        tmp.m[2][2] =   a->m[2][0] * b->m[0][2] +
                        a->m[2][1] * b->m[1][2] +
                        a->m[2][2] * b->m[2][2];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

/**
 * TODO:
 * * There is probably a more efficient way to do this
 * * or at least one that involves a loop so that the
 * * same code doesn't need to be pasted repetitively.
 */
float mat3f_determinant(mat3f* mat)
{
        float dt;
        mat2f sm;

        dt = 0.0f;

        sm.m[0][0] = mat->m[1][1];
        sm.m[0][1] = mat->m[1][2];
        sm.m[1][0] = mat->m[2][1];
        sm.m[1][1] = mat->m[2][2];
        dt += mat->m[0][0] * mat2f_determinant(&sm);

        sm.m[0][0] = mat->m[1][0];
        sm.m[0][1] = mat->m[1][2];
        sm.m[1][0] = mat->m[2][0];
        sm.m[1][1] = mat->m[2][2];
        dt -= mat->m[0][1] * mat2f_determinant(&sm);

        sm.m[0][0] = mat->m[1][0];
        sm.m[0][1] = mat->m[1][1];
        sm.m[1][0] = mat->m[2][0];
        sm.m[1][1] = mat->m[2][1];
        dt += mat->m[0][2] * mat2f_determinant(&sm);

        return dt;
}

void mat3f_transpose(mat3f* mat, mat3f* dest)
{
        int i;
        int j;
        mat3f tmp;
        memcpy(tmp.m, mat->m, CGMATH_MATRIX_SIZE);

        /*for(i = 0; i < CGMATH_MATRIX_HEIGHT; i++) {
                for(j = 0; j < CGMATH_MATRIX_WIDTH; j++) {
                        *(int*)&tmp.m[i][j] ^= *(int*)&tmp.m[j][i];
                        *(int*)&tmp.m[j][i] ^= *(int*)&tmp.m[i][j];
                        *(int*)&tmp.m[i][j] ^= *(int*)&tmp.m[j][i];
                }
        }*/
        *(int*)&tmp.m[0][1] ^= *(int*)&tmp.m[1][0];
        *(int*)&tmp.m[1][0] ^= *(int*)&tmp.m[0][1];
        *(int*)&tmp.m[0][1] ^= *(int*)&tmp.m[1][0];

        *(int*)&tmp.m[0][2] ^= *(int*)&tmp.m[2][0];
        *(int*)&tmp.m[2][0] ^= *(int*)&tmp.m[0][2];
        *(int*)&tmp.m[0][2] ^= *(int*)&tmp.m[2][0];

        memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
}

void mat3f_inverse(mat3f* mat, mat3f* dest)
{
        float dt;
        mat3f tmp;
        mat2f sm;

        dt = mat3f_determinant(mat);

        if(_cgmath_absf(dt) != 0.0f) {
                sm.m[0][0] = mat->m[1][1];
                sm.m[0][1] = mat->m[1][2];
                sm.m[1][0] = mat->m[2][1];
                sm.m[1][1] = mat->m[2][2];
                tmp.m[0][0] = mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[1][0];
                sm.m[0][1] = mat->m[1][2];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][2];
                tmp.m[0][1] = -1.0f * mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[1][0];
                sm.m[0][1] = mat->m[1][1];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][1];
                tmp.m[0][2] = mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[0][1];
                sm.m[0][1] = mat->m[0][2];
                sm.m[1][0] = mat->m[2][1];
                sm.m[1][1] = mat->m[2][2];
                tmp.m[1][0] = -1.0f * mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][2];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][2];
                tmp.m[1][1] = mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[1][0] = mat->m[2][0];
                sm.m[1][1] = mat->m[2][1];
                tmp.m[1][2] = -1.0f * mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[0][1];
                sm.m[0][1] = mat->m[0][2];
                sm.m[1][0] = mat->m[1][1];
                sm.m[1][1] = mat->m[1][2];
                tmp.m[2][0] = mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][2];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][2];
                tmp.m[2][1] = -1.0f * mat2f_determinant(&sm);

                sm.m[0][0] = mat->m[0][0];
                sm.m[0][1] = mat->m[0][1];
                sm.m[1][0] = mat->m[1][0];
                sm.m[1][1] = mat->m[1][1];
                tmp.m[2][2] = mat2f_determinant(&sm);

                mat3f_transpose(&tmp, &tmp);
                mat3f_scale(&tmp, 1.0f/dt, &tmp);
                memcpy(dest->m, tmp.m, CGMATH_MATRIX_SIZE);
        }
}

void mat3f_get_row(mat3f* mat, vec3f* dest, int row)
{
        if(row > 0 && row < CGMATH_MATRIX_HEIGHT) {
                dest->m[0] = mat->m[row][0];
                dest->m[1] = mat->m[row][1];
                dest->m[2] = mat->m[row][2];
        }
}

void mat3f_get_col(mat3f* mat, vec3f* dest, int col)
{
        if(col > 0 && col < CGMATH_MATRIX_WIDTH) {
                dest->m[0] = mat->m[0][col];
                dest->m[1] = mat->m[1][col];
                dest->m[2] = mat->m[2][col];
        }
}

void mat3f_set_row(mat3f* mat, vec3f* src, int row)
{
        if(row > 0 && row < CGMATH_MATRIX_HEIGHT) {
                mat->m[row][0] = src->m[0];
                mat->m[row][1] = src->m[1];
                mat->m[row][2] = src->m[2];
        }
}

void mat3f_set_col(mat3f* mat, vec3f* src, int col)
{
        if(col > 0 && col < CGMATH_MATRIX_WIDTH) {
                mat->m[0][col] = src->m[0];
                mat->m[1][col] = src->m[1];
                mat->m[2][col] = src->m[2];
        }
}

