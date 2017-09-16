#include "bootstrap.h"

void recoveryCol(Col *col) {
	Node *node = col->head;

	while (node != NULL) {
		if (node->left == NULL) {
			node->row->head = node;
		}
		else {
			node->left->right = node;
		}
		if (node->right != NULL) {
			node->right->left = node;
		}
		node->row->length++;

		node = node->down;
	}

	if (col->left != NULL) {
		col->left->right = col;
	}
	else {
		colPointer = col;
	}
	if (col->right != NULL) {
		col->right->left = col;
	}

	return;
}