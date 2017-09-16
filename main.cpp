#include "bootstrap.h"

string filename = "1.in";

Figure figures[FIGURE_NUMBER];

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
}

void readFieldFromFile() {
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

void createReferenceMatrix()
{
    Col *cols[FILLED_PIXELS_NUMBER];
    Node *bottommostNodes[FILLED_PIXELS_NUMBER] = { NULL };

    for (int i = 0; i < FILLED_PIXELS_NUMBER; i++) {
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

        for (int x = 0; x < FILLED_PIXELS_NUMBER; x++) {
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
    Col *currentCol = colPointer,
            *minCol = currentCol;
    int min = currentCol->length;
    currentCol = currentCol->right;
    while (currentCol != NULL) {

        if (min > currentCol->length)
        {
            min = currentCol->length;
            minCol = currentCol;
        }

        currentCol = currentCol->right;
    }
    return minCol;
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

void removeRowsOfEqualFiguresWithCorrectRow(Row *correctRow, stack<ColOrRow> *deletedColRowStack)
{
    Row *row = rowPointer;
    while (row != NULL) {
        if (row->figure == correctRow->figure && row != correctRow) {
            removeRow(row, deletedColRowStack);
        }

        row = row->down;
    }
}

Row *solutions[12];
stack<Row> solutionStack;

bool dancingLinks(int depth = 0){
    if (colPointer == NULL) {
        return true;
    }
    if (rowPointer == NULL) {
        return false;
    }

    stack<ColOrRow> deletedColRowStack;

    Col *leastCol = selectLeastColumn();

    if (leastCol->length == 0) {
        return false;
    }

    Node *probablyCorrectNode = leastCol->head;

    while (probablyCorrectNode != NULL) {
        Row *probablyСorrectRow = probablyCorrectNode->row;

        removeRowsThatNotCorellatedWithCorrectRow(probablyСorrectRow, &deletedColRowStack);
        removeRowsOfEqualFiguresWithCorrectRow(probablyСorrectRow, &deletedColRowStack);
        removeColsThatNotCorellatedWithCorrectRow(probablyСorrectRow, &deletedColRowStack);

        solutions[depth] = probablyСorrectRow;
        solutionStack.push(*probablyСorrectRow);
        removeRow(probablyСorrectRow, &deletedColRowStack);

        bool recursiveResult = dancingLinks(depth + 1);
        restoreColRowStack(&deletedColRowStack);

        if (recursiveResult) {
            return true;
        }

        solutions[depth] = NULL;
        solutionStack.pop();

        probablyCorrectNode = probablyCorrectNode->down;
    }

    return false;
}

void renderFigures() {
    for (int figure = 0; figure < FIGURE_NUMBER; figure++) {
        cout << (figures[figure].needMirror ? "need mirror" : "don't need mirror") << endl;
        for (int mirror = 0; mirror < (figures[figure].needMirror ? 2 : 1); mirror++) {
            cout << "number of turns " << figures[figure].numOfTurn << endl;
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

int main() {
    seedFigures();
    readFieldFromFile();
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
}#define  _CRT_SECURE_NO_WARNINGS
#include "bootstrap.h"

        string filename = "1.in";

Figure figures[FIGURE_NUMBER];

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
}

void readFieldFromFile() {
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

void createReferenceMatrix()
{
    Col *cols[FILLED_PIXELS_NUMBER];
    Node *bottommostNodes[FILLED_PIXELS_NUMBER] = { NULL };

    for (int i = 0; i < FILLED_PIXELS_NUMBER; i++) {
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

        for (int x = 0; x < FILLED_PIXELS_NUMBER; x++) {
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
    Col *currentCol = colPointer,
            *minCol = currentCol;
    int min = currentCol->length;
    currentCol = currentCol->right;
    while (currentCol != NULL) {

        if (min > currentCol->length)
        {
            min = currentCol->length;
            minCol = currentCol;
        }

        currentCol = currentCol->right;
    }
    return minCol;
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

void removeRowsOfEqualFiguresWithCorrectRow(Row *correctRow, stack<ColOrRow> *deletedColRowStack)
{
    Row *row = rowPointer;
    while (row != NULL) {
        if (row->figure == correctRow->figure && row != correctRow) {
            removeRow(row, deletedColRowStack);
        }

        row = row->down;
    }
}

Row *solutions[12];
stack<Row> solutionStack;

bool dancingLinks(int depth = 0){
    if (colPointer == NULL) {
        return true;
    }
    if (rowPointer == NULL) {
        return false;
    }

    stack<ColOrRow> deletedColRowStack;

    Col *leastCol = selectLeastColumn();

    if (leastCol->length == 0) {
        return false;
    }

    Node *probablyCorrectNode = leastCol->head;

    while (probablyCorrectNode != NULL) {
        Row *probablyСorrectRow = probablyCorrectNode->row;

        removeRowsThatNotCorellatedWithCorrectRow(probablyСorrectRow, &deletedColRowStack);
        removeRowsOfEqualFiguresWithCorrectRow(probablyСorrectRow, &deletedColRowStack);
        removeColsThatNotCorellatedWithCorrectRow(probablyСorrectRow, &deletedColRowStack);

        solutions[depth] = probablyСorrectRow;
        solutionStack.push(*probablyСorrectRow);
        removeRow(probablyСorrectRow, &deletedColRowStack);

        bool recursiveResult = dancingLinks(depth + 1);
        restoreColRowStack(&deletedColRowStack);

        if (recursiveResult) {
            return true;
        }

        solutions[depth] = NULL;
        solutionStack.pop();

        probablyCorrectNode = probablyCorrectNode->down;
    }

    return false;
}

void renderFigures() {
    for (int figure = 0; figure < FIGURE_NUMBER; figure++) {
        cout << (figures[figure].needMirror ? "need mirror" : "don't need mirror") << endl;
        for (int mirror = 0; mirror < (figures[figure].needMirror ? 2 : 1); mirror++) {
            cout << "number of turns " << figures[figure].numOfTurn << endl;
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

int main() {
    seedFigures();
    readFieldFromFile();
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