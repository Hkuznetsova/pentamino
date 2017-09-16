#include "bootstrap.h"

Col *selectLeastColumn() {
	Col *currentCol = colPointer,
		*minCol = currentCol;
	int min = currentCol->length;
	currentCol = currentCol->right;
	while (currentCol != NULL) {

		if (min > currentCol->length)
		{
			min = currentCol->length;
			minCol = currentCol;
		}

		currentCol = currentCol->right;
	}
	return minCol;
}