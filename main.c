#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "definitions.h"

int** newMatrix(int width, int height)
{
	int **matrix = (int**) malloc(sizeof(int*) * width);
	int i, j;
	for (i = 0; i < height; i++) {
		matrix[i] = (int*) malloc(sizeof(int) * height);
		for (j = 0; j < height; j++) {
			matrix[i][j] = EMPTY_QUAD;
		}
	}
	return matrix;
}

int **freeMatrix(int **matrix, int width, int height)
{
	int i;
	for (i = 0; i < height; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

bool isPieceWhite(enum Piece piece)
{
	if (piece == PAWN_WHITE || piece == ROOK_WHITE || piece == KNIGHT_WHITE
		|| piece == BISHOP_WHITE || piece == QUEEN_WHITE || piece == KING_WHITE) {
			return true;
	}
	return false;
}

bool isPieceBlack(enum Piece piece)
{
	if (piece == PAWN_BLACK || piece == ROOK_BLACK || piece == KNIGHT_BLACK
		|| piece == BISHOP_BLACK || piece == QUEEN_BLACK || piece == KING_BLACK) {
			return true;
	}
	return false;
}

bool hasPiece(int **matrix, enum Color color, int x, int y)
{
	int piece = matrix[x][y];
	if (piece != EMPTY_QUAD) {
		if (color == ANY_COLOR ||
			color == WHITE && isPieceWhite(piece) ||
			color == BLACK && isPieceBlack(piece)) {
			return true;
		}
	}
	return false;
}

struct Move* newMove(int x, int y)
{
	struct Move *move = (struct Move*) malloc(sizeof(struct Move));
	move->x = x; move->y = y;
	move->next = NULL;
	return move;
}

void insertMove(struct Move **list, struct Move *move)
{
	if (*list == NULL) {
		*list = move;
		return;
	}
	struct Move *pointer = *list;
	while (pointer->next != NULL) {
		pointer = pointer->next;
	}
	pointer->next = move;
}

void freeMoveList(struct Move **list)
{
	struct Move *pointer = *list;
	struct Move *temp;
	while (pointer != NULL) {
		temp = pointer;
		pointer = pointer->next;
		free(temp);
	}
}

struct Move* getPawnMoves(int **matrix, enum Color color, int x, int y)
{
	struct Move *moves = NULL;
	if (color == WHITE) {
		// capture left
		if (x > 0 && y > 0) {
			if (hasPiece(matrix, BLACK, x-1, y-1)) {
				struct Move *move = newMove(x-1, y-1);
				insertMove(&moves, move);
			}
		}
		// capture right
		if (x < 7 && y > 0) {
			if (hasPiece(matrix, BLACK, x+1, y-1)) {
				struct Move *move = newMove(x+1, y-1);
				insertMove(&moves, move);
			}
		}
		// move forward
		if (y > 0) {
			if (!hasPiece(matrix, ANY_COLOR, x, y-1)) {
				struct Move *move = newMove(x, y-1);
				insertMove(&moves, move);
			}
		}
		// opening move
		if (y == 6) {
			if (!hasPiece(matrix, ANY_COLOR, x, y-2)) {
				struct Move *move = newMove(x, y-2);
				insertMove(&moves, move);
			}
		}
	} else if (color == BLACK) {
		// capture left
		if (x > 0 && y < 7) {
			if (hasPiece(matrix, WHITE, x-1, y+1)) {
				struct Move *move = newMove(x-1, y+1);
				insertMove(&moves, move);
			}
		}
		// capture right
		if (x < 7 && y < 7) {
			if (hasPiece(matrix, WHITE, x+1, y+1)) {
				struct Move *move = newMove(x+1, y+1);
				insertMove(&moves, move);
			}
		}
		// move forward
		if (y < 7) {
			if (!hasPiece(matrix, ANY_COLOR, x, y+1)) {
				struct Move *move = newMove(x, y+1);
				insertMove(&moves, move);
			}
		}
		// opening move
		if (y == 1) {
			if (!hasPiece(matrix, ANY_COLOR, x, y+2)) {
				struct Move *move = newMove(x, y+2);
				insertMove(&moves, move);
			}
		}
	}
	return moves;
}

void printMoves(struct Move **list)
{
	if (*list == NULL) {
		return;
	}
	struct Move *pointer = *list;
	int i = 0;
	while (pointer != NULL) {
		printf("\n\n== element %d ==", i);
		printf("\nx = %d", pointer->x);
		printf("\ny = %d", pointer->y);
		pointer = pointer->next;
		i++;
	}
}

int main(int argc, char *argv[])
{
	int **matrix = newMatrix(8, 8);
	matrix[0][6] = PAWN_WHITE;
	matrix[0][1] = PAWN_BLACK;

	struct Move *pawnMoves = getPawnMoves(matrix, WHITE, 0, 6);
	printMoves(&pawnMoves);

	pawnMoves = getPawnMoves(matrix, BLACK, 0, 1);
	printMoves(&pawnMoves);

	freeMoveList(&pawnMoves);
	freeMatrix(matrix, 8, 8);
}