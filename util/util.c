#include "util.h"

/*Get the rows and columns of the current ANSI console under windows:*/
void getConsoleSize(int *columns, int *rows) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

Screen *createScreen(int rows, int cols) {
  Screen *screen = malloc(sizeof(Screen));
  screen->cols = cols;
  screen->rows = rows;
  screen->zbuffer = NULL;
  screen->positions = NULL;
  screen->screen = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    screen->screen[i] = calloc(cols, sizeof(int));
  }
  return screen;
}

int **createZBuff(int cols, int rows) {
  int **buffer = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    buffer[i] = malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      buffer[i][j] = -1;
    }
  }
  return buffer;
}
Vec2i_t *createPosBuffer(int rows, int cols) {
  return calloc(rows * cols, sizeof(Vec2i_t));
}

int **updateState(Screen *screen, State *state) {
  int **oldScreen = screen->screen;
  // create the updated screen:
  screen->screen = malloc(screen->rows * sizeof(int *));
  // Generate the new screen:
  for (int i = 0; i < screen->rows; i++) {
    screen->screen[i] = calloc(screen->cols, sizeof(int));
  }
  // Update the new screen with new data:
  // TODO
  // return the old screen:
  return oldScreen;
}

int getRandomInInterval(int start, int stop) {
  return rand() % (1 + stop - start) + start;
}

// Get a random color for the screen:
void seed(Screen *screen) {
  for (int i = 0; i < screen->rows; i++) {
    for (int j = 0; j < screen->cols; j++) {
      screen->screen[i][j] = getRandomInInterval(2, 7);
    }
  }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void swapf(float *a, float *b) {
  float temp = *a;
  *a = *b;
  *b = temp;
}
// Flip the screen
void flipScreen(Screen *screen) {
  for (int a = 0; a < screen->rows; a++) {
    for (int b = 0; b < screen->cols; b++) {
      swap(&screen->screen[a][b], &screen->screen[screen->rows - a][b]);
    }
  }
}