#include "bootstrap.h"

int
	field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH],
	fieldWidth,
	fieldHeight,
	matrix[FIGURE_PLACEMENT_MAX_NUMBER][FILLED_PIXELS_NUMBER],
	matrixRowsCount;

Col *colPointer;
Row *rowPointer;
Row *solutions[12];

Figure figures[FIGURE_NUMBER];
