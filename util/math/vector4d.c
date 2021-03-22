#include "mathutil.h"

Vec4f_t scalarMultVec4f(float scalar, Vec4f_t vector) {
  return (Vec4f_t){.x = vector.x * scalar,
                   .y = vector.y * scalar,
                   .z = vector.z * scalar,
                   .k = vector.k * scalar};
}

Vec4f_t addVec4f(Vec4f_t a, Vec4f_t b) {
  return (Vec4f_t){
      .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z, .k = a.k + b.k};
}

Vec4f_t subVec4f(Vec4f_t a, Vec4f_t b) {
  return (Vec4f_t){
      .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z, .k = a.k - b.k};
}

float scalarProd4f(Vec4f_t a, Vec4f_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.k * b.k;
}

Vec4f_t normalize(Vec4f_t a) {
  float inverse = 1 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.k * a.k);
  return scalarMultVec4f(inverse, a);
}