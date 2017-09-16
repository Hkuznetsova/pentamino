#ifndef __COL_H__
#define __COL_H__

#include "bootstrap.h"

typedef struct Col {
	struct Col *left = NULL,
		*right = NULL;
	struct Node *head = NULL;
	int length = 0,
		name;
} Col;

#endif