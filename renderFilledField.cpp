#include "bootstrap.h"

void renderFilledField() {
	int correctFieldFilling[60];
	for (int i = 0; i < FIGURE_NUMBER; i++) {
		Node *node = solutions[i]->head;
		while (node != NULL) {
			correctFieldFilling[node->col->name] = solutions[i]->figure;
			node = node->right;
		}
	}

	for (int y = 0; y < fieldHeight; y++) {
		for (int x = 0; x < fieldWidth; x++) {
			int color = field[y][x] ? correctFieldFilling[field[y][x] - 1] : 0;
			setColor(color);
			cout << "  ";
		}
		cout << endl;
	}
}