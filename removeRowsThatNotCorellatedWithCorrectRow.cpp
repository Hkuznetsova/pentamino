#include "bootstrap.h"

void removeRowsThatNotCorellatedWithCorrectRow(Row *correctedRow, stack<ColOrRow> *deletedColRowStack) {
	Node *node = correctedRow->head;
	while (node != NULL) {
		Col *columForDeleting = node->col;
		Node *nodeForDeleting = columForDeleting->head;
		while (nodeForDeleting != NULL)
		{

			Row *rowForDeleting = nodeForDeleting->row;
			if (rowForDeleting != correctedRow)
			{
				removeRow(rowForDeleting, deletedColRowStack);
			}

			nodeForDeleting = nodeForDeleting->down;
		}

		node = node->right;
	}
}