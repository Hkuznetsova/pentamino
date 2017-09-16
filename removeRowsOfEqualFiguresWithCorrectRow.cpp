#include "bootstrap.h"

void removeRowsOfEqualFiguresWithCorrectRow(Row *correctRow, stack<ColOrRow> *deletedColRowStack)
{
	Row *row = rowPointer;
	while (row != NULL) {
		if (row->figure == correctRow->figure && row != correctRow) {
			removeRow(row, deletedColRowStack);
		}

		row = row->down;
	}
}