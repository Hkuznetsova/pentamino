#include "bootstrap.h"

void removeCol(Col *col, stack<ColOrRow> *deletedColRowStack) {
	Node *node = col->head;

	while (node != NULL) {
		if (node->left == NULL) {
			node->row->head = node->right;
		}
		else {
			node->left->right = node->right;
		}
		if (node->right != NULL) {
			node->right->left = node->left;
		}
		node->row->length--;

		node = node->down;
	}

	if (col->left != NULL) {
		col->left->right = col->right;
	}
	else {
		colPointer = col->right;
	}
	if (col->right != NULL) {
		col->right->left = col->left;
	}

	ColOrRow *deletedColOrRow = new ColOrRow;
	deletedColOrRow->col = col;
	(*deletedColRowStack).push(*deletedColOrRow);

	return;
}