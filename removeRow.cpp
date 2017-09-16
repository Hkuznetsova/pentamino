#include "bootstrap.h"

void removeRow(Row *row, stack<ColOrRow> *deletedColRowStack) {
	Node *node = row->head;

	while (node != NULL) {
		if (node->up == NULL) {
			node->col->head = node->down;
		}
		else {
			node->up->down = node->down;
		}
		if (node->down != NULL) {
			node->down->up = node->up;
		}
		node->col->length--;

		node = node->right;
	}

	if (row->up != NULL) {
		row->up->down = row->down;
	}
	else {
		rowPointer = row->down;
	}
	if (row->down != NULL) {
		row->down->up = row->up;
	}

	ColOrRow *deletedColOrRow = new ColOrRow;
	deletedColOrRow->row = row;
	(*deletedColRowStack).push(*deletedColOrRow);

	return;
}
