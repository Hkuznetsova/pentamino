#include "bootstrap.h"

Figure::Figure() { }

Figure::Figure(char nameFigure, int figurePixels[5][2], bool figureMirror, int figureNumOfTurn) {
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

void Figure::turn() {
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

void Figure::mirrorFigure() {
	mirrored = !mirrored;

	for (int i = 0; i < 5; i++)
	{
		int x = pixels[i][0];
		pixels[i][0] = -x;
	}
}