#ifndef __ROW_H__
#define __ROW_H__

#include "bootstrap.h"

typedef struct Row {
	struct Row *up = NULL,
		*down = NULL;
	struct Node *head = NULL;
	int length = 0,
		name,
		figure;
} Row;

#endif