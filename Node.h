#ifndef __NODE_H__
#define __NODE_H__

#include "bootstrap.h"

typedef struct Node {
	struct Node *left = NULL,
		*right = NULL,
		*up = NULL,
		*down = NULL;
	struct Row *row = NULL;
	struct Col *col = NULL;
	int figureType = -1;
} Node;

#endif