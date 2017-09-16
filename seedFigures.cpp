#include "bootstrap.h"

void seedFigures() {
	//F
	int FPixels[5][2] = { { 0,0 },{ 0,1 },{ 1,1 },{ 0,-1 },{ -1,0 } };
	figures[0] = Figure('F', FPixels);

	// I
	int IPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 0,-1 },{ 0, -2 } };
	figures[1] = Figure('I', IPixels, false, 2);

	// L
	int LPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 0,-1 },{ 1,-1 } };
	figures[2] = Figure('L', LPixels);

	// N
	int NPixels[5][2] = { { 0,0 },{ 0,1 },{ 0,2 },{ 1,0 },{ 1,-1 } };
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
}