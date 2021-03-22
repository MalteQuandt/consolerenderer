#pragma once

#ifndef MATRIXU_H
#define MATRIXU_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct mat_t {
  int rows;
  int cols;
  float** elem;  // First dimension are the rows and the second are the columns
                 // of the matrix
} Mat_t;

// Simple matrix operations:
Mat_t* mcreate(int rows, int cols);
int mdestroy(Mat_t* matrix);
Mat_t* mmultiply(Mat_t* matone, Mat_t* mattwo);
void printMatrix(Mat_t* matrix, char *name);

Mat_t* mtranspose(Mat_t* matrix);
void mdelete(Mat_t* matrix);
// Calculate the inverse of a matrix:
Mat_t* minverse(Mat_t* matrix);
// Transform a list of vectors with a specified matrix.
int mtransform(Mat_t* one, Mat_t** matrices, int len);
// Specific matrices:
Mat_t* midentity(int rows);
Mat_t* mviewport(int x, int y, int width, int height, int center);
Mat_t* conLookAt(Mat_t* eye, Mat_t* center, Mat_t* up);
Mat_t* mScalingMatrix(float x, float y, float z);
Mat_t* mTranslation(float x, float y, float z);
Mat_t* mShear(float angle);
Mat_t* mRotationXaxis(float angle);
Mat_t* mRotationYaxis(float angle);
Mat_t* mRotationZaxis(float angle);
Mat_t* mProjectionMatrix(int diffo);

// Vector methods:
Mat_t* mtov(Mat_t* matrix);
Mat_t* vtom(Mat_t* vector);
Mat_t* vcreate(int rows);
Mat_t* vnormalize(Mat_t* vec);
float vgetLength(Mat_t* vec);
Mat_t* vcross(Mat_t* vecone, Mat_t* vectwo);
float vscalarMult(Mat_t* vecone, Mat_t* vectwo);
Mat_t* vscalar(Mat_t* vec, float scalar);
Mat_t* vadd(Mat_t* vecone, Mat_t* vectwo);
Mat_t* vsub(Mat_t* vecone, Mat_t* vectwo);
Mat_t* vSquare(Mat_t* vecone);

// Special vector methods:
Mat_t* vcreate4(float x, float y, float z);
Mat_t* projectVec(Mat_t* vector, int c);
Mat_t* vnormalize3(Mat_t* vector);

#endif