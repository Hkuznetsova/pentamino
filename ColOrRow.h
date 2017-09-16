#ifndef __COL_OR_ROW_H__
#define __COL_OR_ROW_H__

#include "bootstrap.h"

typedef struct ColOrRow {
	struct Col *col = NULL;
	struct Row *row = NULL;
} ColOrRow;

#endif