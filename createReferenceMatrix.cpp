#include "bootstrap.h"

void createReferenceMatrix()
{
	Col *cols[FILLED_PIXELS_NUMBER];
	Node *bottommostNodes[FILLED_PIXELS_NUMBER] = { NULL };

	for (int i = 0; i < FILLED_PIXELS_NUMBER; i++) {
		cols[i] = new Col;
		cols[i]->name = i;
		if (i > 0) {
			cols[i]->left = cols[i - 1];
			cols[i - 1]->right = cols[i];
		}
	}

	colPointer = cols[0];

	Col *currentCol = NULL;
	Row *currentRow = NULL,
		*prevRow = NULL;

	for (int y = 0; y < matrixRowsCount; y++) {
		prevRow = currentRow;
		currentRow = new Row;
		currentRow->name = y;
		if (y == 0) {
			rowPointer = currentRow;
		}
		else {
			prevRow->down = currentRow;
			currentRow->up = prevRow;
		}

		Node *rightmostNode = NULL;

		for (int x = 0; x < FILLED_PIXELS_NUMBER; x++) {
			if (matrix[y][x] == 0) continue;
			currentCol = cols[x];
			currentRow->figure = matrix[y][x];

			Node *currentNode = new Node;
			currentNode->figureType = matrix[y][x];
			currentNode->col = currentCol;
			currentNode->row = currentRow;

			if (rightmostNode == NULL) {
				currentRow->head = currentNode;
			}
			else {
				rightmostNode->right = currentNode;
				currentNode->left = rightmostNode;
			}
			rightmostNode = currentNode;

			if (bottommostNodes[x] == NULL) {
				currentCol->head = currentNode;
			}
			else {
				bottommostNodes[x]->down = currentNode;
				currentNode->up = bottommostNodes[x];
			}
			bottommostNodes[x] = currentNode;

			currentCol->length++;
			currentRow->length++;
		}
	}

}