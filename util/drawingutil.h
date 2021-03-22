#pragma once

#ifndef DRAWINGUTIL_H
#define DRAWINGUTIL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ansicol.h"
#include "math\mathutil.h"

typedef struct screen {
  int rows;       // rows of the field
  int cols;       // columns of the field
  int updateLen;  // Length of the positions buffer
  int **screen;
  int **zbuffer;
  Vec2i_t *positions;
} Screen;

void getConsoleSize(int *columns, int *rows);
void drawScreen(Screen *screen);
void updateScreenSlow(Screen *screen);
// Checks for collisions on the old and new screen and stores the
// list in the screen struct.
int checkUpdataColl(Screen *screen, int **oldScreen);
// Update the screen after creating the new screen and updating the
// collision-list
void updateScreenFast(Screen *screen);
void drawCell(int, int);

// Drawing methods(2d, need to be updated with 3d implementations utilizing the
// z-buffer)
void drawLine(int x0, int y0, int x1, int y1, Screen *screen, int color);
void drawLineFast(int x0, int y0, int x1, int y1, Screen *screen, int color);

void drawLine3dF(Mat_t *start, Mat_t *end, Screen *screen, int color);
void triangle(Mat_t *p1, Mat_t *p2, Mat_t *p3, Screen *screen, int color);

#endif