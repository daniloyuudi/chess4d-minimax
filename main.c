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

struct Move* getRookMoves(int **matrix, enum Color color, int x, int y)
{
	struct Move *moves = NULL;
	int quadsLeft = x;
	int quadsRight = 7-x;
	int quadsUp = y;
	int quadsDown = 7-y;
	int i;
	if (color == WHITE) {
		// move right
		for (i = 1; i <= quadsRight; i++) {
			if (!hasPiece(matrix, WHITE, x+i, y)) {
				struct Move *move = newMove(x+i, y);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x+i, y)) {
				break;
			}
		}
		// move up
		for (i = 1; i <= quadsUp; i++) {
			if (!hasPiece(matrix, WHITE, x, y-i)) {
				struct Move *move = newMove(x, y-i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x, y-i)) {
				break;
			}
		}
		// move left
		for (i = 1; i <= quadsLeft; i++) {
			if (!hasPiece(matrix, WHITE, x-i, y)) {
				struct Move *move = newMove(x-i, y);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x-i, y)) {
				break;
			}
		}
		// move down
		for (i = 1; i <= quadsDown; i++) {
			if (!hasPiece(matrix, WHITE, x, y+i)) {
				struct Move *move = newMove(x, y+i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x, y+i)) {
				break;
			}
		}
	} else if (color == BLACK) {
		// move right
		for (i = 1; i <= quadsRight; i++) {
			if (!hasPiece(matrix, BLACK, x+i, y)) {
				struct Move *move = newMove(x+i, y);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x+i, y)) {
				break;
			}
		}
		// move up
		for (i = 1; i <= quadsUp; i++) {
			if (!hasPiece(matrix, BLACK, x, y-i)) {
				struct Move *move = newMove(x, y-i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x, y-i)) {
				break;
			}
		}
		// move left
		for (i = 1; i <= quadsLeft; i++) {
			if (!hasPiece(matrix, BLACK, x-i, y)) {
				struct Move *move = newMove(x-i, y);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x-i, y)) {
				break;
			}
		}
		// move down
		for (i = 1; i <= quadsDown; i++) {
			if (!hasPiece(matrix, BLACK, x, y+i)) {
				struct Move *move = newMove(x, y+i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x, y+i)) {
				break;
			}
		}
	}
	return moves;
}

int max(int num1, int num2)
{
	return (num1 > num2) ? num1 : num2;
}

int min(int num1, int num2)
{
	return (num1 > num2) ? num2 : num1;
}

struct Move* getBishopMoves(int **matrix, enum Color color, int x, int y)
{
	struct Move *moves = NULL;
	int quadsLeft = x;
	int quadsRight = 7-x;
	int quadsUp = y;
	int quadsDown = 7-y;
	int quadsRightUp = min(quadsRight, quadsUp);
	int quadsLeftUp = min(quadsLeft, quadsUp);
	int quadsLeftDown = min(quadsLeft, quadsDown);
	int quadsRightDown = min(quadsRight, quadsDown);
	int i;
	if (color == WHITE) {
		// move right-up
		for (i = 1; i <= quadsRightUp; i++) {
			if (!hasPiece(matrix, WHITE, x+i, y-i)) {
				struct Move *move = newMove(x+i, y-i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x+i, y-i)) {
				break;
			}
		}
		// move left-up
		for (i = 1; i <= quadsLeftUp; i++) {
			if (!hasPiece(matrix, WHITE, x-i, y-i)) {
				struct Move *move = newMove(x-i, y-i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x-i, y-i)) {
				break;
			}
		}
		// move left-down
		for (i = 1; i <= quadsLeftDown; i++) {
			if (!hasPiece(matrix, WHITE, x-i, y+i)) {
				struct Move *move = newMove(x-i, y+i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x-i, y+i)) {
				break;
			}
		}
		// move right-down
		for (i = 1; i <= quadsRightDown; i++) {
			if (!hasPiece(matrix, WHITE, x+i, y+i)) {
				struct Move *move = newMove(x+i, y+i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x+i, y+i)) {
				break;
			}
		}
	} else if (color == BLACK) {
		// move right-up
		for (i = 1; i <= quadsRightUp; i++) {
			if (!hasPiece(matrix, BLACK, x+i, y-i)) {
				struct Move *move = newMove(x+i, y-i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x+i, y-i)) {
				break;
			}
		}
		// move left-up
		for (i = 1; i <= quadsLeftUp; i++) {
			if (!hasPiece(matrix, BLACK, x-i, y-i)) {
				struct Move *move = newMove(x-i, y-i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x-i, y-i)) {
				break;
			}
		}
		// move left-down
		for (i = 1; i <= quadsLeftDown; i++) {
			if (!hasPiece(matrix, BLACK, x-i, y+i)) {
				struct Move *move = newMove(x-i, y+i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x-i, y+i)) {
				break;
			}
		}
		// move right-down
		for (i = 1; i <= quadsRightDown; i++) {
			if (!hasPiece(matrix, BLACK, x+i, y+i)) {
				struct Move *move = newMove(x+i, y+i);
				insertMove(&moves, move);
			}
			if (hasPiece(matrix, ANY_COLOR, x+i, y+i)) {
				break;
			}
		}
	}
	return moves;
}

struct Move* getKnightMoves(int **matrix, enum Color color, int x, int y)
{
	struct Move *moves = NULL;
	if (color == WHITE) {
		// move left then up
		if (x > 1 && y > 0) {
			if (!hasPiece(matrix, WHITE, x-2, y-1)) {
				struct Move *move = newMove(x-2, y-1);
				insertMove(&moves, move);
			}
		}
		// move up then left
		if (x > 0 && y > 1) {
			if (!hasPiece(matrix, WHITE, x-1, y-2)) {
				struct Move *move = newMove(x-1, y-2);
				insertMove(&moves, move);
			}
		}
		// move up then right
		if (x < 7 && y > 1) {
			if (!hasPiece(matrix, WHITE, x+1, y-2)) {
				struct Move *move = newMove(x+1, y-2);
				insertMove(&moves, move);
			}
		}
		// move right then up
		if (x < 6 && y > 0) {
			if (!hasPiece(matrix, WHITE, x+2, y-1)) {
				struct Move *move = newMove(x+2, y-1);
				insertMove(&moves, move);
			}
		}
		// move right then down
		if (x < 6 && y < 7) {
			if (!hasPiece(matrix, WHITE, x+2, y+1)) {
				struct Move *move = newMove(x+2, y+1);
				insertMove(&moves, move);
			}
		}
		// move down then right
		if (x < 7 && y < 6) {
			if (!hasPiece(matrix, WHITE, x+1, y+2)) {
				struct Move *move = newMove(x+1, y+2);
				insertMove(&moves, move);
			}
		}
		// move down then left
		if (x > 0 && y < 6) {
			if (!hasPiece(matrix, WHITE, x-1, y+2)) {
				struct Move *move = newMove(x-1, y+2);
				insertMove(&moves, move);
			}
		}
		// move left then down
		if (x > 1 && y < 7) {
			if (!hasPiece(matrix, WHITE, x-2, y+1)) {
				struct Move *move = newMove(x-2, y+1);
				insertMove(&moves, move);
			}
		}
	} else if (color == BLACK) {
		// move left then up
		if (x > 1 && y > 0) {
			if (!hasPiece(matrix, BLACK, x-2, y-1)) {
				struct Move *move = newMove(x-2, y-1);
				insertMove(&moves, move);
			}
		}
		// move up then left
		if (x > 0 && y > 1) {
			if (!hasPiece(matrix, BLACK, x-1, y-2)) {
				struct Move *move = newMove(x-1, y-2);
				insertMove(&moves, move);
			}
		}
		// move up then right
		if (x < 7 && y > 1) {
			if (!hasPiece(matrix, BLACK, x+1, y-2)) {
				struct Move *move = newMove(x+1, y-2);
				insertMove(&moves, move);
			}
		}
		// move right then up
		if (x < 6 && y > 0) {
			if (!hasPiece(matrix, BLACK, x+2, y-1)) {
				struct Move *move = newMove(x+2, y-1);
				insertMove(&moves, move);
			}
		}
		// move right then down
		if (x < 6 && y < 7) {
			if (!hasPiece(matrix, BLACK, x+2, y+1)) {
				struct Move *move = newMove(x+2, y+1);
				insertMove(&moves, move);
			}
		}
		// move down then right
		if (x < 7 && y < 6) {
			if (!hasPiece(matrix, BLACK, x+1, y+2)) {
				struct Move *move = newMove(x+1, y+2);
				insertMove(&moves, move);
			}
		}
		// move down then left
		if (x > 0 && y < 6) {
			if (!hasPiece(matrix, BLACK, x-1, y+2)) {
				struct Move *move = newMove(x-1, y+2);
				insertMove(&moves, move);
			}
		}
		// move left then down
		if (x > 1 && y < 7) {
			if (!hasPiece(matrix, BLACK, x-2, y+1)) {
				struct Move *move = newMove(x-2, y+1);
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
	//matrix[0][1] = PAWN_BLACK;
	matrix[0][6] = PAWN_WHITE;
	matrix[4][4] = KNIGHT_WHITE;

	printf("==knight moves==");
	struct Move *knightMoves = getKnightMoves(matrix, WHITE, 4, 4);
	printMoves(&knightMoves);

	freeMoveList(&knightMoves);
	freeMatrix(matrix, 8, 8);
}