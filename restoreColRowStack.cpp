#include "bootstrap.h"

void restoreColRowStack(stack<ColOrRow> *deletedColRowStack) {
	while (!(*deletedColRowStack).empty())
	{
		ColOrRow *colOrRow = &(*deletedColRowStack).top();

		if (colOrRow->col != NULL) {
			recoveryCol(colOrRow->col);
			colOrRow->col = NULL;
		}
		if (colOrRow->row != NULL) {
			recoveryRow(colOrRow->row);
			colOrRow->row = NULL;
		}

		(*deletedColRowStack).pop();

		//	delete colOrRow;
	}
}