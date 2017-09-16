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
		Row *probably�orrectRow = probablyCorrectNode->row;

		removeRowsThatNotCorellatedWithCorrectRow(probably�orrectRow, &deletedColRowStack);
		removeRowsOfEqualFiguresWithCorrectRow(probably�orrectRow, &deletedColRowStack);
		removeColsThatNotCorellatedWithCorrectRow(probably�orrectRow, &deletedColRowStack);

		solutions[depth] = probably�orrectRow;
		removeRow(probably�orrectRow, &deletedColRowStack);

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