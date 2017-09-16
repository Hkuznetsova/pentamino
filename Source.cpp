#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <stack>
#include <conio.h>
#include <windows.h>

using namespace std;

int field[60][60],
	fieldWidth,
	fieldHeight,
	matrix[4000][60],
	matrixRowsCount;

string filename = "8.in";

int cellNum = 1;

struct Figure{

	char name;
	int numOfTurn;
	bool needMirror;

	int pixels[5][2];

	int turnNumber;
	bool mirrored = false;
	
	Figure() {
	}

	Figure(char nameFigure, int figurePixels[5][2], bool figureMirror = true, int figureNumOfTurn = 4) {
		name = nameFigure;
		needMirror = figureMirror;
		numOfTurn = figureNumOfTurn;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				pixels[i][j] = figurePixels[i][j];
			}
		}
		
		mirrored = false;
		turnNumber = 0;
	}
	// œÓ‚ÓÓÚ ÙË„Û˚
	void turn() {
		turnNumber++;
		if (turnNumber == numOfTurn) {
			turnNumber = 0;
		}

		for (int i = 0; i < 5; i++)
		{
			int x = pixels[i][0];
			int y = pixels[i][1];

			pixels[i][0] = y;
			pixels[i][1] = -x;
		}
	}


	// ŒÚÁÂÍ‡ÎË‚‡ÌËÂ ÙË„Û˚
	void mirrorFigure() {
		mirrored = !mirrored;

		for (int i = 0; i < 5; i++)
		{
			int x = pixels[i][0];
			pixels[i][0] = -x;
		}

	}

} figures[12];

void seedFigures() {
	//F
	int FPixels[5][2] = { {0,0}, {0,1}, {1,1}, {0,-1}, {-1,0} };
	figures[0] = Figure('F', FPixels);

	// I
	int IPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 0,-1 },{ 0, -2 } };
	figures[1] = Figure('I', IPixels, false, 2);

	// L
	int LPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 0,-1 },{ 1,-1 } };
	figures[2] = Figure('L', LPixels);

	// N
	int NPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{1,0 },{ 1,-1 } };
	figures[3] = Figure('N', NPixels);

	// P
	int PPixels[5][2] = { { 0,0 },{ 1,0 },{ 0,1 },{ 0,-1 },{ 1,-1 } };
	figures[4] = Figure('P', PPixels);

	// T
	int TPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 1,0 },{ -1,0 } };
	figures[5] = Figure('T', TPixels, false);

	// U
	int UPixels[5][2] = { { 0,0 },{ 0,1 },{ 1,1 },{ 0,-1 },{ 1,-1 } };
	figures[6] = Figure('U', UPixels, false);

	// V
	int VPixels[5][2] = { { 0,0 },{ 1,0 },{ 2,0 },{ 0,-1 },{ 0,-2 } };
	figures[7] = Figure('V', VPixels, false);

	// W
	int WPixels[5][2] = { { 0,0 },{ -1,1 },{ -1,0 },{ 0,-1 },{ 1,-1 } };
	figures[8] = Figure('W', WPixels, false);

	// X
	int XPixels[5][2] = { { 0,0 },{ 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
	figures[9] = Figure('X', XPixels, false, 1);

	// Y
	int YPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 1,0 },{ 0,-1 } };
	figures[10] = Figure('Y', YPixels);

	// Z
	int ZPixels[5][2] = { { 0,0 },{ 0,1 },{ -1,1 },{ 0,-1 },{ 1,-1 } };
	figures[11] = Figure('Z', ZPixels, true, 2);


	//// test
	//int iPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,-1 },{ 0,0 },{ 0,0 } };
	//figures[0] = Figure('i', iPixels, false);

	//// test
	//int testPixels[5][2] = { { 0,0 },{ 0,1 },{ -1,0 },{ 0,0 },{ 0,0 } };
	//figures[1] = Figure('t', testPixels, false);
}

void readFieldFromFile() {
	field[60][60] = { 0 };

	ifstream file(filename);
	string str;

	int	y = 0;
		
	fieldWidth = 0;
	fieldHeight = 0;


	while (getline(file, str))
	{
		int strSize = str.size();
		fieldWidth = max(fieldWidth, strSize);
		for (int x = 0; x < strSize; x++)
		{
			if (str[x] == 'o') {
				field[y][x] = cellNum;
				cellNum++;
			}
			else {
				field[y][x] = 0;
			}
		}
		y++;
	}
	fieldWidth++;
	fieldHeight = y;
	file.close();
	cellNum--;
}

void createMatrix() {
	for (int y = 0; y < fieldHeight; y++)
	{
		for (int x = 0; x < fieldWidth; x++)
		{
			if (field[y][x] == 0) {
				continue;
			}
			for (int i = 0; i < 12; i++)
			{
				do { //ÔÂÂ·Ó ÓÚÁÂÍ‡ÎË‚‡ÌËÈ
					int turns = 0;
					do { //ÔÂÂ·Ó ÔÓ‚ÓÓÚÓ‚
						bool filled = false;
						int arrayOfCellSolutions[5], ai = 0;
						for (int j = 0; j < 5; j++)
						{
							int fy = y + figures[i].pixels[j][1];
							int fx = x + figures[i].pixels[j][0];

							if (field[fy][fx] == 0 || fy < 0 || fx < 0 || fy >= fieldHeight || fx >= fieldWidth) {
								filled = false;
								break;
							}
							else
							{
								arrayOfCellSolutions[ai] = field[fy][fx];
								ai++;
								filled = true;
							}
						}

						if (filled == true) {
							for (int t = 0; t < 5; t++)
							{
								matrix[matrixRowsCount][arrayOfCellSolutions[t] - 1] = i + 1;
							}
							matrixRowsCount++;
						}


						figures[i].turn();
						turns++;
					} while (turns < figures[i].numOfTurn);

					if (figures[i].needMirror == true)
					{
						figures[i].mirrorFigure();
					}
				} while (figures[i].mirrored != false);


			}
		}
	}
}

typedef struct Node {
	struct Node *left = NULL, 
		*right = NULL, 
		*up = NULL, 
		*down = NULL;
	struct Row *row = NULL;
	struct Col *col = NULL;
	int figureType = -1;
} Node;

typedef struct Row {
	struct Row *up = NULL, 
		*down = NULL;
	struct Node *head = NULL;
	int length = 0, 
		name,
		figure;
} Row;

typedef struct Col {
	struct Col *left = NULL,
		*right = NULL;
	struct Node *head = NULL;
	int length = 0,
		name;
} Col;

typedef struct ColOrRow {
	struct Col *col = NULL;
	struct Row *row = NULL;
} ColOrRow;

Col *colPointer;
Row *rowPointer;


void checkReferenceMatrixRows() {
	Row *currentRow = rowPointer;

	while (currentRow != NULL) {

		cout << currentRow->name << "  " << currentRow->length << endl;
		currentRow = currentRow->down;
	}


}

void checkReferenceMatrixCols() {
	Col *currentCol = colPointer;

	while (currentCol != NULL) {

		cout << currentCol->name << "  " << currentCol->length << endl;
		currentCol = currentCol->right;
	}

}

void checkReferenceMatrix()
{
	cout << "ROWS" << endl;
	checkReferenceMatrixRows();
	cout << "COLS" << endl;
	checkReferenceMatrixCols();
}

void createReferenceMatrix()
{
	Col *cols[60];
	Node *bottommostNodes[60] = { NULL };

	for (int i = 0; i < cellNum; i++) {
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

		for (int x = 0; x < cellNum; x++) {
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

void removeRow(Row *row, stack<ColOrRow> *deletedColRowStack) {
	Node *node = row->head;

	while (node != NULL) {
		if (node->up == NULL) {
			node->col->head = node->down;
		}
		else {
			node->up->down = node->down;
		}
		if (node->down != NULL) {
			node->down->up = node->up;
		}
		node->col->length--;

		node = node->right;
	}

	if (row->up != NULL) {
		row->up->down = row->down;
	}
	else {
		rowPointer = row->down;
	}
	if (row->down != NULL) {
		row->down->up = row->up;
	}

	ColOrRow *deletedColOrRow = new ColOrRow;
	deletedColOrRow->row = row;
	(*deletedColRowStack).push(*deletedColOrRow);
//	cout << "push to stack Row " << row->name << endl;

	return;
}


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

//	cout << "push to stack Col " << col->name << endl;

	return;
}


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

Col *selectLeastColumn() {
	Col *curentCol = colPointer,
		*minCol = NULL;
	int min = 4000;
	while (curentCol != NULL) {

		if (min > curentCol->length)
		{
			min = curentCol->length;
			minCol = curentCol;
		}

		curentCol = curentCol->right;
	}
	return minCol;
}

unsigned long long getTotalSystemMemory()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
}

void restoreColRowStack(stack<ColOrRow> *deletedColRowStack) {
	while (!(*deletedColRowStack).empty())
	{
		ColOrRow *colOrRow = &(*deletedColRowStack).top();

		if (colOrRow->col != NULL) {
			recoveryCol(colOrRow->col);
			colOrRow->col = NULL;
//			cout << "pop from stack Col " << colOrRow->col->name << endl;
		}
		if (colOrRow->row != NULL) {
			recoveryRow(colOrRow->row);
			colOrRow->row = NULL;
//			cout << "pop from stack Row " << colOrRow->row->name << endl;
		}

		(*deletedColRowStack).pop();

	//	delete colOrRow;
	}
}

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

void removeColsThatNotCorellatedWithCorrectRow(Row *correctedRow, stack<ColOrRow> *deletedColRowStack) {
	Node *node = correctedRow->head;
	while (node != NULL) {
		Col *columForDeleting = node->col;
		removeCol(columForDeleting, deletedColRowStack);
		node = node->right;
	}
}


void setColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((color << 4) | 15));
}

void renderRow(Row *row) {
	int color = rand() % 13 + 1;
	int correctFieldFilling[60];
	for (int i = 0; i < 60; i++) correctFieldFilling[i] = 15;
	Node *node = row->head;
	while (node != NULL) {
		correctFieldFilling[node->col->name] = color;
		node = node->right;
	}

	for (int y = 0; y < fieldHeight; y++) {
		for (int x = 0; x < fieldWidth; x++) {
			int color = field[y][x] ? correctFieldFilling[field[y][x] - 1] : 0;
			setColor(color);
			cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void removeRowsOfEqualFiguresWithCorrectRow(Row *correctRow, stack<ColOrRow> *deletedColRowStack) 
{
/*	if (correctRow->name == 707) {
		cout << "correct row " << correctRow->name << endl;
		renderRow(correctRow);
	}*/

	/*if (correctRow->figure == 4) {
		cout << "correct row " << correctRow->name << endl;
		renderRow(correctRow);
		//cout << "deleted" << endl;
	}*/

	Row *row = rowPointer;
	while (row != NULL) {
		if (row->figure == correctRow->figure && row != correctRow) {
			removeRow(row, deletedColRowStack);

			/*if (correctRow->name == 707 && row->name == 1445) {
				cout << "deleted " << row->name << endl;
				renderRow(row);
			}*/

			/*if (correctRow->figure == 12) {
				renderRow(row);
			}*/
		}

		row = row->down;
	}
}

Row *solutions[12];
stack<Row> solutionStack;

bool dancingLinks(int depth = 0){
//	cout << endl << endl << "new " << depth << endl;
//	checkReferenceMatrix();
//	cout << endl;
	if (colPointer == NULL) {
//		cout << "back 1" << endl << endl;
		return true;
	}
	if (rowPointer == NULL) {
//		cout << "back 2" << endl << endl;
		return false;
	}

	stack<ColOrRow> deletedColRowStack;

	Col *leastCol = selectLeastColumn();

	if (leastCol->length == 0) {
//		cout << "back 3" << endl << endl;
		return false;
	}

	Node *probablyCorrectNode = leastCol->head;
	
	while (probablyCorrectNode != NULL) {
		Row *probably—orrectRow = probablyCorrectNode->row;

		removeRowsThatNotCorellatedWithCorrectRow(probably—orrectRow, &deletedColRowStack);
		removeRowsOfEqualFiguresWithCorrectRow(probably—orrectRow, &deletedColRowStack);
		removeColsThatNotCorellatedWithCorrectRow(probably—orrectRow, &deletedColRowStack);
		
		solutions[depth] = probably—orrectRow;
		solutionStack.push(*probably—orrectRow);
		removeRow(probably—orrectRow, &deletedColRowStack);
		
		bool recursiveResult = dancingLinks(depth + 1);
//		cout << "leave call with result " << (recursiveResult ? "true" : "false") << endl;
//		cout << "restore " << endl;
		restoreColRowStack(&deletedColRowStack);
//		checkReferenceMatrix();

		if (recursiveResult) {
//			cout << "back4" << endl << endl;
			return true;
		}

		solutions[depth] = NULL;
		solutionStack.pop();

		probablyCorrectNode = probablyCorrectNode->down;
	}

	return false;
//	cout << "back5" << endl << endl;
}

void renderFilledField() {
	int correctFieldFilling[60];
	for (int i = 0; i < 12; i++) {
		Node *node = solutions[i]->head;
		while (node != NULL) {
			//cout << node->col->name << " ";
			correctFieldFilling[node->col->name] = solutions[i]->figure;
			node = node->right;
		}
		//cout << endl;
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

void renderFigures() {
	for (int figure = 0; figure < 12; figure++) {
		cout << (figures[figure].needMirror ? "need mirror" : "don't need mirror") << endl;
		for (int mirror = 0; mirror < (figures[figure].needMirror ? 2 : 1); mirror++) {
			for (int i = 0; i < figures[figure].numOfTurn; i++) {
				for (int y = -2; y <= 2; y++) {
					for (int x = -2; x <= 2; x++) {
						bool filled = false;
						for (int pixel = 0; pixel < 5; pixel++) {
							if (figures[figure].pixels[pixel][0] == x && figures[figure].pixels[pixel][1] == y) {
								filled = true;
								break;
							}
						}
						setColor(filled ? figure + 1 : 0);
						cout << "  ";
					}
					setColor(0);
					cout << endl;
				}
				cout << endl << endl;
				figures[figure].turn();
			}
			figures[figure].mirrorFigure();
		}
		cout << endl << endl;
	}
}

int main() {
	seedFigures();
	readFieldFromFile();
	createMatrix();
	createReferenceMatrix();
	//freopen("repetition.out", "w", stdout);
	//checkReferenceMatrix();

	if (!dancingLinks()) {
		cout << "This field does not have any solutions.";
		_getch();
		return 0;
	}

	renderFilledField();
	//1 
	/*Row *row = rowPointer;
	while (row != NULL) {
		if (row->figure == 12) {
			cout << row->name << endl;
			renderRow(row);
			int i = 0;
		}
		row = row->down;
	}*/

	/*Row *row = rowPointer;
	while (row != NULL) {
		if (row->name == 149) {
			cout << "name " << row->name << endl;
			cout << "figure " << row->figure << endl;
			renderRow(row);
			break;
		}
		row = row->down;
	}*/
	_getch();
	return 0;
}