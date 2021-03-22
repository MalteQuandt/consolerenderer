#include "drawingutil.h"

#include "util.h"
void drawLine(int x0, int y0, int x1, int y1, Screen *screen, int color) {
  for (float step = 0.; step < 1.; step += .003) {
    int x = x0 + (x1 - x0) * step;
    int y = y0 + (y1 - y0) * step;
    // ugly branch effectively making this code error proof.
    if (x >= screen->cols || y >= screen->rows) continue;
    screen->screen[y][x] = color;
  }
}

void drawLineFast(int x0, int y0, int x1, int y1, Screen *screen, int color) {
  // if (dx>dy) {for (int x)} else {for (int y)}
  char steep = 0;
  // check if the difference of x is bigger than the difference in y.
  if (abs(x0 - x1) < abs(y0 - y1)) {
    swap(&x0, &y0);
    swap(&x1, &y1);
    steep = 1;
  }

  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }

  for (int x = x0; x <= x1; x++) {
    float t = (x - x0) / (float)(x1 - x0);
    int y = y0 * (1. - t) + y1 * t;
    if (steep) {
      screen->screen[x][y] = color;
    } else {
      screen->screen[y][x] = color;
    }
  }
}

// Just a little wrapper to show that drawing the old fashioned way is just
// not viable:
void updateScreenSlow(Screen *screen) { drawScreen(screen); }
// Fast way of updating the screen:
void updateScreenFast(Screen *screen) {
  if (screen->updateLen == -1) {
    return;
  }
  for (int i = 0; i < screen->updateLen + 1; i++) {
    int row = screen->positions[i].y;
    int col = screen->positions[i].x;
    printf(MOVETERMTOINT, row, col);  // jump to the position to be drawn.
    drawCell(screen->screen[row][col], 1);
  }
}

int checkUpdataColl(Screen *screen, int **oldScreen) {
  int posBuffPosition = -1;
  screen->updateLen = 0;
  for (int row = 0; row < screen->rows; row++) {
    for (int col = 0; col < screen->cols; col++) {
      if (screen->screen[row][col] != oldScreen[row][col]) {
        // Save this coordinate and increase coordinate length!
        posBuffPosition++;
        screen->positions[posBuffPosition].x = col;
        screen->positions[posBuffPosition].y = row;
      }
    }
  }
  screen->updateLen = posBuffPosition;
  free(oldScreen);  // It is no longer needed!
  return 1;
}

void drawScreen(Screen *screen) {
  char *color = NULL;
  for (int i = 0; i < screen->rows; i++) {
    for (int j = 0; j < screen->cols; j++) {
      switch (screen->screen[i][j]) {
        case 0:
          color = BLCB;
          break;
        case 1:
          color = REDB;
          break;
        case 2:
          color = GRNB;
          break;
        case 3:
          color = YELB;
          break;
        case 4:
          color = BLUB;
          break;
        case 5:
          color = MAGB;
          break;
        case 6:
          color = CYNB;
          break;
        case 7:
          color = WHTB;
          break;
      }
      printf("%s " RESET, color);
    }
  }
}

void drawCell(int cellData, int colorf) {
  if (colorf) {
    char *color = NULL;
    switch (cellData) {
      case 0:
        color = BLCB;
        break;
      case 1:
        color = REDB;
        break;
      case 2:
        color = GRNB;
        break;
      case 3:
        color = YELB;
        break;
      case 4:
        color = BLUB;
        break;
      case 5:
        color = MAGB;
        break;
      case 6:
        color = CYNB;
        break;
      case 7:
        color = WHTB;
        break;
    }
    printf("%s " RESET, color);
  } else {
    printf("%d", cellData);
  }
}

void drawLine3dF(Mat_t *start, Mat_t *end, Screen *screen, int color) {
  int steep = 0;
  if (abs(start->elem[0][0] - end->elem[0][0]) <
      abs(start->elem[1][0] - end->elem[1][0])) {
    swapf(&start->elem[0][0], &start->elem[1][0]);
    swapf(&end->elem[0][0], &end->elem[1][0]);
  }
  if (start->elem[0][0] > end->elem[1][0]) {
    Mat_t *temp = start;
    start = end;
    end = temp;
  }

  for (int x = start->elem[0][0]; x <= end->elem[0][0]; x++) {
    float t =
        (x - end->elem[0][0]) / (float)(start->elem[0][0] - end->elem[0][0]);
    int y = start->elem[1][0] * (1. - t) + end->elem[1][0] * t + .5;
    if (steep) {
      screen->screen[x][y] = color;
    } else {
      screen->screen[y][x] = color;
    }
  }
}