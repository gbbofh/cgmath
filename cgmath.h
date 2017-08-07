/**
 * File: cgmath.h
 * Author: Garrett Bates <garrett.bates@cs.nmt.edu>
 * Description:
 * * A basic vector and matrix maths library meant
 * * for use with OpenGL, written in pure C.
 */

#ifndef CGMATH_H
#define CGMATH_H

#include "cgmath_core.h"

#define VEC_X   0
#define VEC_Y   1
#define VEC_Z   2
#define VEC_W   3

#define MAT2F_SIZE      (2 * 2 * sizeof(float))
#define MAT3F_SIZE      (3 * 3 * sizeof(float))
#define MAT4F_SIZE      (4 * 4 * sizeof(float))

typedef struct {
        float m[2];
} vec2f;

typedef struct {
        float m[3];
} vec3f;

typedef struct {
        float m[4];
} vec4f, quat;

typedef struct {
        float m[2][2];
} mat2f;

typedef struct {
        float m[3][3];
} mat3f;

typedef struct {
        float m[4][4];
} mat4f;

/**
 * Implementation: vec2f.c
 * Description:
 * * Interface for a simple 2 dimensional
 * * vector of floating point values
 */
void    vec2f_zero(vec2f* vec);
void    vec2f_identity(vec2f* vec, int axis);
void    vec2f_add(vec2f* a, vec2f* b, vec2f* dest);
void    vec2f_scale(vec2f* vec, float scalar, vec2f* dest);
float   vec2f_scalar_prod(vec2f* a, vec2f* b);

float   vec2f_sqr_mag(vec2f* vec);
void    vec2f_normalize(vec2f* vec, vec2f* dest);

/**
 * Implementation: vec3f.c
 * Description:
 * * Interface for a simple 3 dimensional
 * * vector of floating point values
 */
void    vec3f_zero(vec3f* vec);
void    vec3f_identity(vec3f* vec, int axis);
void    vec3f_add(vec3f* a, vec3f* b, vec3f* dest);
void    vec3f_scale(vec3f* vec, float scalar, vec3f* dest);
float   vec3f_scalar_prod(vec3f* a, vec3f* b);
void    vec3f_vector_prod(vec3f* a, vec3f* b, vec3f* dest);

float   vec3f_sqr_mag(vec3f* vec);
void    vec3f_normalize(vec3f* vec, vec3f* dest);

/**
 * Implementation: vec4f.c
 * Description:
 * * Interface for a simple 4 dimensional
 * * vector of floating point values
 */
void    vec4f_zero(vec4f* vec);
void    vec4f_identity(vec4f* vec, int axis);
void    vec4f_add(vec4f* a, vec4f* b, vec4f* dest);
void    vec4f_scale(vec4f* vec, float scalar, vec4f* dest);
float   vec4f_scalar_prod(vec4f* a, vec4f* b);

float   vec4f_sqr_mag(vec4f* vec);
void    vec4f_normalize(vec4f* vec, vec4f* dest);

/**
 * Implementation: mat2f.c
 * Description:
 * * Interface for a simple 2x2 matrix
 * * of floating point values. For use
 * * with Open GL, the matrix must be
 * * transposed before it is supplied
 * * to a shader or anything.
 */
void    mat2f_zero(mat2f* mat);
void    mat2f_identity(mat2f* mat);
void    mat2f_add(mat2f* a, mat2f* b, mat2f* dest);
void    mat2f_scale(mat2f* mat, float scalar, mat2f* dest);
void    mat2f_multiply(mat2f* a, mat2f* b, mat2f* dest);
float   mat2f_determinant(mat2f* mat);
void    mat2f_transpose(mat2f* mat, mat2f* dest);
void    mat2f_inverse(mat2f* mat, mat2f* dest);

void    mat2f_get_row(mat2f* mat, vec2f* dest, int row);
void    mat2f_get_col(mat2f* mat, vec2f* dest, int col);
void    mat2f_set_row(mat2f* mat, vec2f* src, int row);
void    mat2f_set_col(mat2f* mat, vec2f* src, int col);

/**
 * Implementation: mat3f.c
 * Description:
 * * Interface for a simple 3x33matrix
 * * of floating point values. For use
 * * with Open GL, the matrix must be
 * * transposed before it is supplied
 * * to a shader or anything.
 */
void    mat3f_zero(mat3f* mat);
void    mat3f_identity(mat3f* mat);
void    mat3f_add(mat3f* a, mat3f* b, mat3f* dest);
void    mat3f_scale(mat3f* mat, float scalar, mat3f* dest);
void    mat3f_multiply(mat3f* a, mat3f* b, mat3f* dest);
float   mat3f_determinant(mat3f* mat);
void    mat3f_transpose(mat3f* mat, mat3f* dest);
void    mat3f_inverse(mat3f* mat, mat3f* dest);

void    mat3f_get_row(mat3f* mat, vec3f* dest, int row);
void    mat3f_get_col(mat3f* mat, vec3f* dest, int col);
void    mat3f_set_row(mat3f* mat, vec3f* src, int row);
void    mat3f_set_col(mat3f* mat, vec3f* src, int col);

/**
 * Implementation: mat4f.c
 * Description:
 * * Interface for a simple 4x4 matrix
 * * of floating point values. For use
 * * with Open GL, the matrix must be
 * * transposed before it is supplied
 * * to a shader or anything.
 */
void    mat4f_zero(mat4f* mat);
void    mat4f_identity(mat4f* mat);
void    mat4f_add(mat4f* a, mat4f* b, mat4f* dest);
void    mat4f_scale(mat4f* mat, float scalar, mat4f* dest);
void    mat4f_multiply(mat4f* a, mat4f* b, mat4f* dest);
float   mat4f_determinant(mat4f* mat);
void    mat4f_transpose(mat4f* mat, mat4f* dest);
void    mat4f_inverse(mat4f* mat, mat4f* dest);

void    mat4f_get_row(mat4f* mat, vec4f* dest, int row);
void    mat4f_get_col(mat4f* mat, vec4f* dest, int col);
void    mat4f_set_row(mat4f* mat, vec4f* src, int row);
void    mat4f_set_col(mat4f* mat, vec4f* src, int col);

#endif

