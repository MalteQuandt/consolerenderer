// Header file for functions describing geometrical objects:
#pragma once

#ifndef GOBJ_H
#define GOBJ_H

#include "mathutil.h"

// Defining a geometric object structure made out of specific points.
typedef struct gobj {
  int count;
  Mat_t* object;
} GObj;

#endif