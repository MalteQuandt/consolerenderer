#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "util\ansimov.h"
#include "util\drawingutil.h"
#include "util\math\mathutil.h"
#include "util\math\matrix.h"
#include "util\util.h"

void testDrawScreen(Screen* screen);

int main(void) {
  // Draw a point to the screen with the | Viewport * Projection * View * Model
  // * point |chain

  int rows = 0, cols = 0;
  getConsoleSize(&cols, &rows);
  Screen* screen = createScreen(
      rows - 1, cols);  // -1 as the first row will be pushed outside the
  // terminal view at the end of the drawing.
  screen->zbuffer = createZBuff(cols, rows - 1);
  screen->positions = createPosBuffer(rows - 1, cols);
  printf("\e[1;1H\e[2J");  // clear the console screen
  int** oldScreen = NULL;
  for (int i = 0; i < 120; i++) {
    printf(MOVETERMTOINT, 0, 0);
    oldScreen = updateState(screen, NULL);
    drawLineFast(i + 1, 5, i + 20, 5, screen, 1);
    drawLineFast(i + 20, 5, i + 20, 20, screen, 1);
    drawLineFast(i + 20, 20, i + 1, 20, screen, 1);
    drawLineFast(i + 1, 20, i + 1, 5, screen, 1);
    checkUpdataColl(screen, oldScreen);
    updateScreenFast(screen);
    if (i == 119) {
      for (i = 120; i != 0; i--) {
        printf(MOVETERMTOINT, 0, 0);
        oldScreen = updateState(screen, NULL);
        drawLineFast(i + 1, 5, i + 20, 5, screen, 1);
        drawLineFast(i + 20, 5, i + 20, 20, screen, 1);
        drawLineFast(i + 20, 20, i + 1, 20, screen, 1);
        drawLineFast(i + 1, 20, i + 1, 5, screen, 1);
        checkUpdataColl(screen, oldScreen);
        updateScreenFast(screen);
      }
    }
  }
  // Not nessecarry, as the operating system just clears up after the process
  // exits. Just done for fun.
  free(screen->screen);
  free(screen->zbuffer);
  free(screen->positions);
  free(screen);
}

void testDrawScreen(Screen* screen) {
  for (int i = 0; i < screen->rows; i++) {
    for (int j = 0; j < screen->cols; j++) {
      drawCell(screen->screen[i][j], 1);
    }
  }
}
