#ifndef __FIGURE_H__
#define __FIGURE_H__

typedef struct Figure {
	char name;
	int numOfTurn;
	bool needMirror;

	int pixels[5][2];

	int turnNumber;
	bool mirrored = false;

	Figure();
	Figure(char nameFigure, int figurePixels[5][2], bool figureMirror = true, int figureNumOfTurn = 4);

	void turn();
	void mirrorFigure();
} Figure;

#endif