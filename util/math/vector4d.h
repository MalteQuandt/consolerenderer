#pragma once

#ifndef VECTOR_H
#define VECTOR_H

// 2 dimensional vector represented with cartesian coordiantes:
typedef struct vec2i_t {
  int x;
  int y;
} Vec2i_t;

// 4 dimensional vector represented with cartesian coordinates.
typedef struct vec4f_t {
  float x;
  float y;
  float z;
  float k;
} Vec4f_t;

// Multiplying a vector with a scalar:
Vec4f_t scalarMultVec4f(float, Vec4f_t);

// Adding two vectors:
Vec4f_t addVec4f(Vec4f_t, Vec4f_t);

// Subtracting two vectors:
Vec4f_t subVec4f(Vec4f_t, Vec4f_t);

// Get the scalar product of two vectors:
float scalarProd4f(Vec4f_t, Vec4f_t);

Vec4f_t normalize(Vec4f_t);

#endif