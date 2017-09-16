#define  _CRT_SECURE_NO_WARNINGS
#include "bootstrap.h"

int main() {
	seedFigures();

	string filename;
	cout << "Type filename: ";
	cin >> filename;

	readFieldFromFile(filename);
	createMatrix();
	createReferenceMatrix();

	if (!dancingLinks()) {
		cout << "This field does not have any solutions.";
	}
	else {
		renderFilledField();
	}
	
	
	_getch();
	return 0;
}