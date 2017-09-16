#include "bootstrap.h"

void removeColsThatNotCorellatedWithCorrectRow(Row *correctedRow, stack<ColOrRow> *deletedColRowStack) {
	Node *node = correctedRow->head;
	while (node != NULL) {
		Col *columForDeleting = node->col;
		removeCol(columForDeleting, deletedColRowStack);
		node = node->right;
	}
}