#include "bootstrap.h"

void readFieldFromFile(string filename) {
	ifstream file(filename);
	string str;

	int	y = 0;

	fieldWidth = 0;
	fieldHeight = 0;

	int cellNumber = 1;

	while (getline(file, str))
	{
		int strSize = str.size();
		fieldWidth = max(fieldWidth, strSize);
		for (int x = 0; x < strSize; x++)
		{
			if (str[x] == 'o') {
				field[y][x] = cellNumber;
				cellNumber++;
			}
			else {
				field[y][x] = 0;
			}
		}
		y++;
	}
	if (cellNumber - 1 != FILLED_PIXELS_NUMBER) {
		throw new exception("Number of filled pixels in input figure must be 60.");
	}
	fieldWidth++;
	fieldHeight = y;
	file.close();
}
