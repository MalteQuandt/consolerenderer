#include "mathutil.h"

Mat4d_t identity4 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

Vec4f_t transform(Mat4d_t* matrix, Vec4f_t* vector) {
  Vec4f_t temp = {.x = 0, .y = 0, .z = 0, .k = 0};
  // There is an error here! need to transpose the calc:
  temp.x = matrix->unitx.x * vector->x + matrix->unity.x * vector->y +
           matrix->unitz.x * vector->z + matrix->unitk.x * vector->k;
  temp.y = matrix->unitx.y * vector->x + matrix->unity.y * vector->y +
           matrix->unitz.y * vector->z + matrix->unitk.y * vector->k;
  temp.z = matrix->unitx.z * vector->x + matrix->unity.z * vector->y +
           matrix->unitz.z * vector->z + matrix->unitk.z * vector->k;
  temp.k = matrix->unitx.k * vector->x + matrix->unity.k * vector->y +
           matrix->unitz.k * vector->z + matrix->unitk.k * vector->k;
  return temp;
}
Vec4f_t multiply(Mat4d_t* matrix, Vec4f_t* vector) {
  transform(matrix, vector);
}
void multiplyp(Mat4d_t* matrix, Vec4f_t* vector) {
  transformVec(matrix, vector);
}

void multiplypa(Mat4d_t* matrix, Vec4f_t* vector, int len) {
  transformArr(matrix, vector, len);
}
void transformVec(Mat4d_t* matrix, Vec4f_t* vector) {
  Vec4f_t temp = {.x = 0, .y = 0, .z = 0, .k = 0};
  // Calculate transformation:
  temp.x = scalarProd4f(matrix->unitx, *vector);
  temp.y = scalarProd4f(matrix->unity, *vector);
  temp.z = scalarProd4f(matrix->unitz, *vector);
  temp.k = scalarProd4f(matrix->unitk, *vector);
  // Apply transformation:
  vector->x = temp.x;
  vector->y = temp.y;
  vector->z = temp.z;
  vector->k = temp.k;
}

void transformArr(Mat4d_t* matrix, Vec4f_t* vector, int len) {
  for (int pos = 0; pos < len; pos++) {
    transformVec(matrix, vector + pos);
  }
}

Mat4d_t transpose(Mat4d_t* mat) {
  Mat4d_t temp = {0};
  temp.unitx = (Vec4f_t){.x = mat->unitx.x,
                         .y = mat->unity.x,
                         .z = mat->unitz.x,
                         .k = mat->unitk.x};
  temp.unity = (Vec4f_t){.x = mat->unitx.y,
                         .y = mat->unity.y,
                         .z = mat->unitz.y,
                         .k = mat->unitk.y};
  temp.unitz = (Vec4f_t){.x = mat->unitx.z,
                         .y = mat->unity.z,
                         .z = mat->unitz.z,
                         .k = mat->unitk.z};
  temp.unitk = (Vec4f_t){.x = mat->unitx.k,
                         .y = mat->unity.k,
                         .z = mat->unitz.k,
                         .k = mat->unitk.k};
  return temp;
}

Mat4d_t inverse(Mat4d_t* matrix) {

}