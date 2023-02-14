#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <stdbool.h>
#include "definitions.h"

int** newMatrix();
int** copyMatrix(int **matrix);
void freeMatrix(int **matrix);
void movePiece(int **matrix, int originX, int originY, int destinationX, int destinationY);

#endif