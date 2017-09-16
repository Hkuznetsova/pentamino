#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "bootstrap.h"

extern int
	field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH],
	fieldWidth,
	fieldHeight,
	matrix[FIGURE_PLACEMENT_MAX_NUMBER][FILLED_PIXELS_NUMBER],
	matrixRowsCount;

extern Col *colPointer;
extern Row *rowPointer;
extern Row *solutions[12];

extern Figure figures[FIGURE_NUMBER];

#endif