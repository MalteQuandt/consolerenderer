#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include "vector4d.h"

typedef struct {
  Vec4f_t unitx;
  Vec4f_t unity;
  Vec4f_t unitz;
  Vec4f_t unitk;
} Mat4d_t;

Vec4f_t transform(Mat4d_t*, Vec4f_t*);
void transformVec(Mat4d_t*, Vec4f_t*);

Vec4f_t multiply(Mat4d_t*, Vec4f_t*);
void multiplyp(Mat4d_t*, Vec4f_t*);
void multiplypa(Mat4d_t* matrix, Vec4f_t* vector, int len);
// Transform an array of vectors (and change the original vector)
void transformArr(Mat4d_t*, Vec4f_t*, int len);

Mat4d_t transpose(Mat4d_t*);
void transposep(Mat4d_t*);
Mat4d_t inverse(Mat4d_t*);
Mat4d_t combineMatrix2(Mat4d_t*, Mat4d_t*);
Mat4d_t combineMatrixn(Mat4d_t*, int len);

#endif

/*
{.unitx = (Vec4f_t){.x = 1, .y = 0, .z = 0, .k = 0},
                     .unity = (Vec4f_t){.x = 0, .y = 1, .z = 0, .k = 0},
                     .unitz = (Vec4f_t){.x = 0, .y = 0, .z = 1, .k = 0},
                     .unitk = (Vec4f_t){.x = 0, .y = 0, .z = 0, .k = 1}};
*/