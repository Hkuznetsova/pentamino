#include "bootstrap.h"

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
				do { //перебор отзеркаливаний
					int turns = 0;
					do { //перебор поворотов
						bool filled = false;
						int arrayOfCellSolutions[FIGURE_SIZE], ai = 0;
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