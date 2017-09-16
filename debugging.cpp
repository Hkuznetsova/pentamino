//#pragma once
//#include "bootstrap.h"
//
//
//void checkReferenceMatrixRows() {
//	Row *currentRow = rowPointer;
//
//	while (currentRow != NULL) {
//
//		cout << currentRow->name << "  " << currentRow->length << endl;
//		currentRow = currentRow->down;
//	}
//
//
//}
//
//void checkReferenceMatrixCols() {
//	Col *currentCol = colPointer;
//
//	while (currentCol != NULL) {
//
//		cout << currentCol->name << "  " << currentCol->length << endl;
//		currentCol = currentCol->right;
//	}
//
//}
//
//void checkReferenceMatrix()
//{
//	cout << "ROWS" << endl;
//	checkReferenceMatrixRows();
//	cout << "COLS" << endl;
//	checkReferenceMatrixCols();
//}
//
//void renderRow(Row *row) {
//	int color = rand() % 13 + 1;
//	int correctFieldFilling[60];
//	for (int i = 0; i < 60; i++) correctFieldFilling[i] = 15;
//	Node *node = row->head;
//	while (node != NULL) {
//		correctFieldFilling[node->col->name] = color;
//		node = node->right;
//	}
//
//	for (int y = 0; y < fieldHeight; y++) {
//		for (int x = 0; x < fieldWidth; x++) {
//			int color = field[y][x] ? correctFieldFilling[field[y][x] - 1] : 0;
//			setColor(color);
//			cout << "  ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//
//void renderFigures() {
//	for (int figure = 0; figure < FIGURE_NUMBER; figure++) {
//		cout << (figures[figure].needMirror ? "need mirror" : "don't need mirror") << endl;
//		for (int mirror = 0; mirror < (figures[figure].needMirror ? 2 : 1); mirror++) {
//			cout << "number of turns " << figures[figure].numOfTurn << endl;
//			for (int i = 0; i < figures[figure].numOfTurn; i++) {
//				for (int y = -2; y <= 2; y++) {
//					for (int x = -2; x <= 2; x++) {
//						bool filled = false;
//						for (int pixel = 0; pixel < 5; pixel++) {
//							if (figures[figure].pixels[pixel][0] == x && figures[figure].pixels[pixel][1] == y) {
//								filled = true;
//								break;
//							}
//						}
//						setColor(filled ? figure + 1 : 0);
//						cout << "  ";
//					}
//					setColor(0);
//					cout << endl;
//				}
//				cout << endl << endl;
//				figures[figure].turn();
//			}
//			figures[figure].mirrorFigure();
//		}
//		cout << endl << endl;
//	}
//}