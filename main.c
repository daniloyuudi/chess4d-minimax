#include <stdio.h>
#include "definitions.h"
#include "matrix.h"
#include "move.h"
#include "tree.h"
#include "piece.h"

int main(int argc, char *argv[])
{
	int **matrix = newMatrix();
	matrix[0][1] = PAWN_BLACK;
	matrix[0][6] = PAWN_WHITE;
	matrix[4][4] = QUEEN_WHITE;

	printf("==king moves==");
	struct Move *kingMoves = getKingMoves(matrix, WHITE, 4, 4);
	printMoves(&kingMoves);

	freeMoveList(&kingMoves);
	freeMatrix(matrix);
}