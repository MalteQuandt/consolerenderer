#include "matrix.h"

Mat_t* mcreate(int rows, int cols) {
  Mat_t* temp = malloc(sizeof(Mat_t));
  temp->cols = cols;
  temp->rows = rows;
  temp->elem = malloc(rows * sizeof(float*));
  for (int i = 0; i < rows; i++) {
    temp->elem[i] = calloc(cols, sizeof(float));
  }
  return temp;
}
int mdestroy(Mat_t* matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    free(matrix->elem[i]);
  }
  free(matrix->elem);
  free(matrix);
}
Mat_t* mtranspose(Mat_t* matrix) {
  Mat_t* temp = mcreate(matrix->rows, matrix->cols);
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      temp->elem[i][j] = matrix->elem[j][i];
    }
  }
  return temp;
}
Mat_t* mmultiply(Mat_t* matone, Mat_t* mattwo) {
  if (matone->cols != mattwo->rows) {
    return 0;
  } else {
    Mat_t* result = mcreate(matone->rows, mattwo->cols);
    for (int i = 0; i < matone->rows; i++) {
      for (int j = 0; j < mattwo->cols; j++) {
        result->elem[i][j] = 0;
        for (int k = 0; k < matone->cols; k++) {
          result->elem[i][j] += matone->elem[i][k] * mattwo->elem[k][j];
        }
      }
    }
    return result;
  }
}
Mat_t* midentity(int rows) {
  Mat_t* temp = mcreate(rows, rows);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      temp->elem[i][j] = i == j ? 1 : 0;
    }
  }
  return temp;
}
// Utilize the gauss-jordan-algo to calculate the inver of a square matrix.
Mat_t* minverse(Mat_t* matrix) {
  if (matrix->rows != matrix->cols) {
    return 0;
  } else {
    Mat_t* result = mcreate(matrix->rows, matrix->cols * 2);
    for (int i = 0; i < matrix->rows; i++) {
      for (int j = 0; j < matrix->cols; j++) {
        result->elem[i][j] = matrix->elem[i][j];
      }
    }
    for (int i = 0; i < matrix->rows; i++)
      result->elem[i][i + matrix->cols] = 1;
    for (int i = 0; i < matrix->rows - 1; i++) {
      // normalize the first row
      for (int j = result->cols - 1; j >= 0; j--) {
        result->elem[i][j] /= result->elem[i][i];
      }
      for (int k = i + 1; k < matrix->rows; k++) {
        float coeff = result->elem[k][i];
        for (int j = 0; j < result->cols; j++) {
          result->elem[k][j] -= result->elem[i][j] * coeff;
        }
      }
    }
    for (int j = result->cols - 1; j >= matrix->rows - 1; j--) {
      result->elem[matrix->rows - 1][j] /=
          result->elem[matrix->rows - 1][matrix->rows - 1];
    }
    for (int i = matrix->rows - 1; i > 0; i--) {
      for (int k = i - 1; k >= 0; k--) {
        float coeff = result->elem[k][i];
        for (int j = 0; j < result->cols; j++) {
          result->elem[k][j] -= result->elem[i][j] * coeff;
        }
      }
    }
    Mat_t* trunc = mcreate(matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
      for (int j = 0; j < matrix->cols; j++) {
        trunc->elem[i][j] = result->elem[i][j + matrix->cols];
      }
    }
    return trunc;
  }
}

// Vector methods:

Mat_t* vnormalize(Mat_t* vec) {
  if (vec->cols > 1) return 0;
  Mat_t* temp = mcreate(vec->rows, vec->cols);

  return temp;
}

float vgetLength(Mat_t* vec) {
  float sum = 0;
  for (int i = 0; i < vec->rows; i++) sum += vec->elem[i][0] * vec->elem[i][0];
  return sqrt(sum);
}

Mat_t* vcross(Mat_t* vecone, Mat_t* vectwo) {
  if (vecone->rows != 3 || vectwo->rows != 3 || vectwo->rows != vecone->rows ||
      vectwo->cols != 1 || vecone->cols != 1) {
    return 0;
  } else {
    // Calculate the 3d cross product
    Mat_t* temp = mcreate(3, 1);
    temp->elem[0][0] = vecone->elem[1][0] * vectwo->elem[2][0] -
                       vecone->elem[2][0] * vectwo->elem[1][0];
    temp->elem[1][0] = vecone->elem[2][0] * vectwo->elem[0][0] -
                       vecone->elem[0][0] * vectwo->elem[2][0];
    temp->elem[2][0] = vecone->elem[0][0] * vectwo->elem[1][0] -
                       vecone->elem[1][0] * vectwo->elem[0][0];
    return temp;
  }
}

float vscalarMult(Mat_t* vecone, Mat_t* vectwo) {
  if (vecone->cols > 1 || vectwo->cols > 1) return 0;
  float sum = 0;
  for (int i = 0; i < vecone->rows; i++) {
    sum += vecone->elem[i][0] * vectwo->elem[i][0];
  }
  return sum;
}

Mat_t* vscalar(Mat_t* vec, float scalar) {
  Mat_t* temp = mcreate(vec->rows, 1);
  for (int i = 0; i < vec->rows; i++) {
    temp->elem[i][0] = vec->elem[i][0] * scalar;
  }
  return temp;
}

Mat_t* vadd(Mat_t* vecone, Mat_t* vectwo) {
  if (vecone->cols > 1 || vectwo->cols > 1) return 0;
  Mat_t* temp = mcreate(vecone->rows, 1);
  for (int i = 0; i < vecone->rows; i++) {
    temp->elem[i][0] = vectwo->elem[i][0] + vectwo->elem[i][0];
  }
  return temp;
}

Mat_t* vsub(Mat_t* vecone, Mat_t* vectwo) {
  if (vecone->cols > 1 || vectwo->cols > 1) return 0;
  Mat_t* temp = mcreate(vecone->rows, 1);
  for (int i = 0; i < vecone->rows; i++) {
    temp->elem[i][0] = vectwo->elem[i][0] - vectwo->elem[i][0];
  }
  return temp;
}

Mat_t* vSquare(Mat_t* vecone) {
  if (vecone->cols > 1) return 0;
  Mat_t* temp = mcreate(vecone->rows, 1);
  for (int i = 0; i < vecone->rows; i++) {
    temp->elem[i][0] = vecone->elem[i][0] * vecone->elem[i][0];
  }
  return temp;
}

Mat_t* vcreate(int rows) { return mcreate(rows, 1); }

Mat_t* mviewport(int x, int y, int width, int height, int depth) {
  Mat_t* temp = midentity(4);
  temp->elem[0][3] = x + width / 2.;
  temp->elem[1][3] = y + height / 2.;
  temp->elem[2][3] = depth / 2.;

  temp->elem[0][0] = width / 2.;
  temp->elem[1][1] = height / 2.;
  temp->elem[2][2] = depth / 2.;
  return temp;
}
Mat_t* conLookAt(Mat_t* eye, Mat_t* center, Mat_t* up) {
  Mat_t* modelview = NULL;
  Mat_t* z = vnormalize(vsub(eye, center));
  Mat_t* x = vnormalize(vcross(up, z));
  Mat_t* y = vnormalize(vsub(z, x));

  Mat_t* min = midentity(4);
  Mat_t* tr = midentity(4);
  for (int i = 0; i < 3; i++) {
    min->elem[0][i] = x->elem[i][0];
    min->elem[1][i] = y->elem[i][0];
    min->elem[2][i] = z->elem[i][0];
    tr->elem[i][3] = -center->elem[i][0];
  }
  return mmultiply(min, tr);
}

Mat_t* mTranslation(float x, float y, float z) {
  Mat_t* trans = midentity(4);
  trans->elem[0][3] = x;
  trans->elem[1][3] = y;
  trans->elem[2][3] = z;
  return trans;
}

Mat_t* mScalingMatrix(float x, float y, float z) {
  Mat_t* scale = midentity(4);
  scale->elem[0][0] = x;
  scale->elem[1][1] = y;
  scale->elem[2][2] = z;
  return scale;
}

Mat_t* mShear(float angle) {
  Mat_t* shear = midentity(4);
  shear->elem[0][1] = 1 / tan(angle);
  shear->elem[1][1] = 0;
  return shear;
}

Mat_t* mRotationXaxis(float angle) {
  Mat_t* rot = midentity(4);
  rot->elem[1][1] = cos(angle);
  rot->elem[1][2] = sin(angle);
  rot->elem[2][1] = -sin(angle);
  rot->elem[2][2] = cos(angle);
  return rot;
}
Mat_t* mRotationYaxis(float angle) {
  Mat_t* rot = midentity(4);
  rot->elem[0][0] = cos(angle);
  rot->elem[0][2] = -sin(angle);
  rot->elem[2][0] = sin(angle);
  rot->elem[2][2] = cos(angle);
  return rot;
}
Mat_t* mRotationZaxis(float angle) {
  Mat_t* rot = midentity(4);
  rot->elem[0][0] = cos(angle);
  rot->elem[0][1] = -sin(angle);
  rot->elem[1][0] = sin(angle);
  rot->elem[1][1] = cos(angle);
  return rot;
}
Mat_t* mProjectionMatrix(int diffo) {
  Mat_t* projm = midentity(4);
  projm->elem[3][2] = 1. / (float)diffo;
  return projm;
}
Mat_t* vcreate4(float x, float y, float z) {
  Mat_t* temp = vcreate(4);
  temp->elem[0][0] = x;
  temp->elem[1][0] = y;
  temp->elem[2][0] = z;
  temp->elem[3][0] = 1;
  return temp;
}

Mat_t* projectVec(Mat_t* vector, int c) {
  Mat_t* temp = NULL;
  Mat_t* mprojection = mProjectionMatrix(c);
  temp = mmultiply(mprojection, vector);
  free(mprojection);

  temp->elem[0][0] = temp->elem[0][0] / temp->elem[3][0];
  temp->elem[1][0] = temp->elem[1][0] / temp->elem[3][0];
  temp->elem[2][0] = temp->elem[2][0] / temp->elem[3][0];
  temp->elem[3][0] = 0;
  return temp;
}

void printMatrix(Mat_t* matrix, char* name) {
  printf("%s: \n", name == NULL ? "Matrix" : name);
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      printf("%f ; ", matrix->elem[i][j]);
    }
    printf("\n");
  }
}
// Delete a specific matrix
void mdelete(Mat_t* matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    free(matrix->elem[i]);
  }
  free(matrix->elem);
  free(matrix);
}

Mat_t* vnormalize3(Mat_t* vector) {
  float sum = 0;
  for (int i = 0; i < vector->rows; i++) {
    sum += (vector->elem[i][0] * vector->elem[i][0]);
  }
  sum = (float)sqrt(sum);
  return vcreate4(vector->elem[0][0] / sum, vector->elem[1][0] / sum,
                  vector->elem[2][0] / sum);
}