#include <stdlib.h>
#include "matrix.h"

int** newMatrix()
{
	int **matrix = (int**) malloc(sizeof(int*) * 8);
	int i, j;
	for (i = 0; i < 8; i++) {
		matrix[i] = (int*) malloc(sizeof(int) * 8);
		for (j = 0; j < 8; j++) {
			matrix[i][j] = EMPTY_QUAD;
		}
	}
	return matrix;
}

int** copyMatrix(int **matrix)
{
	int **newMatrix = (int**) malloc(sizeof(int*) * 8);
	int i, j;
	for (i = 0; i < 8; i++) {
		newMatrix[i] = (int*) malloc(sizeof(int) * 8);
		for (j = 0; j < 8; j++) {
			newMatrix[i][j] = matrix[i][j];
		}
	}
	return newMatrix;
}

void freeMatrix(int **matrix)
{
	int i;
	for (i = 0; i < 8; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void movePiece(int **matrix, int originX, int originY, int destinationX, int destinationY)
{
	matrix[destinationX][destinationY] = matrix[originX][originY];
	matrix[originX][originY] = EMPTY_QUAD;
}