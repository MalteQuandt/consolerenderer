#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdlib.h>
#include <windows.h>

#include "ansimov.h"
#include "drawingutil.h"
#include "math\mathutil.h"
// State of the run-time;
typedef struct state {
  int vertLen;  // Amount of vertices in the renderer.
  Vec4f_t *vertices;
} State;
void getConsoleSize(int *, int *);
Screen *createScreen(int rows, int cols);
int getRandomInInterval(int start, int stop);
Vec2i_t *createPosBuffer(int rows, int cols);
int **createZBuff(int cols, int rows);
// Update the screen and returns the old screen:
int **updateState(Screen *screen, State *state);
void swap(int *a, int *b);
void swapf(float *a, float *b);
void seed(Screen *screen);
void flipScreen(Screen* screen);
#endif