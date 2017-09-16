#include "bootstrap.h"

bool dancingLinks(int depth) {
	if (colPointer == NULL) {
		return true;
	}
	if (rowPointer == NULL) {
		return false;
	}

	stack<ColOrRow> deletedColRowStack;

	Col *leastCol = selectLeastColumn();

	if (leastCol->length == 0) {
		return false;
	}

	Node *probablyCorrectNode = leastCol->head;

	while (probablyCorrectNode != NULL) {
		Row *probablyÑorrectRow = probablyCorrectNode->row;

		removeRowsThatNotCorellatedWithCorrectRow(probablyÑorrectRow, &deletedColRowStack);
		removeRowsOfEqualFiguresWithCorrectRow(probablyÑorrectRow, &deletedColRowStack);
		removeColsThatNotCorellatedWithCorrectRow(probablyÑorrectRow, &deletedColRowStack);

		solutions[depth] = probablyÑorrectRow;
		removeRow(probablyÑorrectRow, &deletedColRowStack);

		bool recursiveResult = dancingLinks(depth + 1);
		restoreColRowStack(&deletedColRowStack);

		if (recursiveResult) {
			return true;
		}

		solutions[depth] = NULL;

		probablyCorrectNode = probablyCorrectNode->down;
	}

	return false;
}