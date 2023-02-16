#include <stdio.h>
#include "definitions.h"
#include "matrix.h"
#include "move.h"
#include "tree.h"
#include "piece.h"

int main(int argc, char *argv[])
{
	int **matrix = newMatrix();
	int i;
	matrix[0][1] = PAWN_BLACK;
	matrix[0][6] = PAWN_WHITE;
	matrix[4][4] = QUEEN_WHITE;

	matrix[0][0] = ROOK_BLACK;
	matrix[1][0] = KNIGHT_BLACK;
	matrix[2][0] = BISHOP_BLACK;
	matrix[3][0] = QUEEN_BLACK;
	matrix[4][0] = KING_BLACK;
	matrix[5][0] = BISHOP_BLACK;
	matrix[6][0] = KNIGHT_BLACK;
	matrix[7][0] = ROOK_BLACK;
	for (i = 0; i < 8; i++) {
		matrix[i][1] = PAWN_BLACK;
	}

	matrix[0][7] = ROOK_WHITE;
	matrix[1][7] = KNIGHT_WHITE;
	matrix[2][7] = BISHOP_WHITE;
	matrix[3][7] = QUEEN_WHITE;
	matrix[4][7] = KING_WHITE;
	matrix[5][7] = BISHOP_WHITE;
	matrix[6][7] = KNIGHT_WHITE;
	matrix[7][7] = ROOK_WHITE;
	for (i = 0; i < 8; i++) {
		matrix[i][6] = PAWN_WHITE;
	}

	struct Node *tree = generateTree(matrix, 4);
	int maxDepth = getTreeMaxDepth(tree);
	printf("maxDepth=%d", maxDepth);

	freeTree(tree);
	freeMatrix(matrix);
}