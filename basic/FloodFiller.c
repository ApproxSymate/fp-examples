/*
 * FloodFiller.c
 *
 *  Created on: Oct 26, 2017
 *      Author: himeshi
 *
 * Portions Copyright 2017 National University of Singapore
 *
 * The C version of the imagefill Java code of the EnerJ benchmark.
 * https://sampa.cs.washington.edu/new/research/approximation/enerj.html
 */

/*
 * Compile with: /home/himeshi/Projects/Approx/llvm/build/bin/clang -I /home/himeshi/Projects/Approx/klee/klee/include -emit-llvm -c -g floodfill.c
 * Run with: /home/himeshi/Projects/Approx/klee/klee/Release+Asserts/bin/klee --precision --max-depth=2 floodfill.bc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "klee/klee.h"

#define WIDTH 1
#define HEIGHT 1
#define MAX_STACK_SIZE 2

int *xstack;
int *ystack;
int stackSize;
int image[WIDTH][HEIGHT];
int targetColor;
int maxStackSize;

int fill(int x, int y);
int getPix(int x, int y);
void setPix(int x, int y, int c);
int popx();
int popy();
void fillLine(int x1, int x2, int y);
void push(int x, int y);

int main() {
  int x, y;

  klee_make_symbolic(image, sizeof image, "__arr32__image");
  klee_make_symbolic(&targetColor, sizeof targetColor, "targetColor");
  klee_make_symbolic(&x, sizeof x, "x");
  //klee_make_symbolic(&y, sizeof y, "y");

  klee_track_error(image, "image_err");
  klee_track_error(&targetColor, "targetColor_err");
  klee_track_error(&x, "x_err");
  //klee_track_error(&y, "y_err");

  //initialize
  //targetColor = 2;
  stackSize = 0;
  maxStackSize = MAX_STACK_SIZE;
  xstack = (int *) malloc(sizeof(int) * maxStackSize);
  ystack = (int *) malloc(sizeof(int) * maxStackSize);

  fill(x, y);
}

int getPix(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return -1;
  else
    return image[x][y];
}

void setPix(int x, int y, int c) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return;
  else
    image[x][y] = c;
}

int popx() {
  if (stackSize == 0)
    return -1;
  else
    return xstack[stackSize - 1];
}

int popy() {
  int value = ystack[stackSize - 1];
  stackSize--;
  return value;
}

void fillLine(int x1, int x2, int y) {
  int x;
  if (x1 > x2) {
    int t = x1;
    x1 = x2;
    x2 = t;
  }
  for (x = x1; x <= x2; x++)
    setPix(x, y, targetColor);
}

void push(int x, int y) {
  stackSize++;
  if (stackSize == MAX_STACK_SIZE) {
    int *newXStack = (int *) malloc(sizeof(int) * maxStackSize * 2);
    int *newYStack = (int *) malloc(sizeof(int) * maxStackSize * 2);
    memcpy(newXStack, xstack, sizeof(int) * maxStackSize);
    memcpy(newYStack, ystack, sizeof(int) * maxStackSize);
    xstack = newXStack;
    ystack = newYStack;
    maxStackSize *= 2;
  }
  xstack[stackSize - 1] = x;
  ystack[stackSize - 1] = y;
}

int fill(int x, int y) {
  int width = WIDTH;
  int height = HEIGHT;
  int color = getPix(x, y);
  fillLine(x, x, y);
  int newColor = getPix(x, y);
  setPix(x, y, color);

  if (color == newColor)
    return -1;

  stackSize = 0;
  push(x, y);

  while (1) {
    x = popx();
    if (x == -1)
      return 1;
    y = popy();

    if (getPix(x, y)!=color) continue;
    int x1 = x;
    int x2 = x;

    while (getPix(x1, y)==color && x1>=0) x1--; // find start of scan-line
    x1++;

    while (getPix(x2, y)==color && x2<width) x2++;  // find end of scan-line
    x2--;

    fillLine(x1,x2,y); // fill scan-line

    int inScanLine = 0;
    int i;
    for (i = x1; i <= x2; i++) { // find scan-lines above this one
      if (!inScanLine && y > 0 && getPix(i, y - 1) == color) {
	push(i, y - 1);
	inScanLine = 1;
      } else if (inScanLine && y > 0 && getPix(i, y - 1) != color)
	inScanLine = 0;
    }

    inScanLine = 0;
    for (i = x1; i <= x2; i++) { // find scan-lines below this one
      if (!inScanLine && y < height - 1 && getPix(i, y + 1) == color) {
	push(i, y + 1);
	inScanLine = 1;
      } else if (inScanLine && y < height - 1
		 && getPix(i, y + 1) != color)
	inScanLine = 0;
    }
  }
}

