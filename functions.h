#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "bootstrap.h"

void seedFigures();
void readFieldFromFile(std::string filename);
void createMatrix();
void createReferenceMatrix();
Col *selectLeastColumn();
void recoveryRow(Row *row);
void recoveryCol(Col *col);
void removeCol(Col *col, std::stack<ColOrRow> *deletedColRowStack);
void removeColsThatNotCorellatedWithCorrectRow(Row *correctedRow, std::stack<ColOrRow> *deletedColRowStack);
void removeRow(Row *row, std::stack<ColOrRow> *deletedColRowStack);
void removeRowsOfEqualFiguresWithCorrectRow(Row *correctRow, std::stack<ColOrRow> *deletedColRowStack);
void removeRowsThatNotCorellatedWithCorrectRow(Row *correctedRow, std::stack<ColOrRow> *deletedColRowStack);
void restoreColRowStack(std::stack<ColOrRow> *deletedColRowStack);
bool dancingLinks(int depth = 0);
void setColor(int color);
void renderFilledField();

#endif