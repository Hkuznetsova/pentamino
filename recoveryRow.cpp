#include "bootstrap.h"

void recoveryRow(Row *row) {
	Node *node = row->head;

	while (node != NULL) {
		if (node->up == NULL) {
			node->col->head = node;
		}
		else {
			node->up->down = node;
		}
		if (node->down != NULL) {
			node->down->up = node;
		}
		node->col->length++;

		node = node->right;
	}

	if (row->up != NULL) {
		row->up->down = row;
	}
	else {
		rowPointer = row;
	}
	if (row->down != NULL) {
		row->down->up = row;
	}

	return;
}