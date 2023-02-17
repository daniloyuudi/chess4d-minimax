#include "minimax.h"
#include "definitions.h"
#include "constants.h"
#include <stdbool.h>

double getPawnEvaluation(enum Color color, int x, int y)
{
	double evaluationWhite[][] = {
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
		{1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
		{0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
		{0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
		{0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
		{0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
	};
	double evaluationBlack[][] = {
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
		{0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
		{0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
		{0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
		{1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
		{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
	};
	if (color == WHITE) {
		return evaluationWhite[x][y];
	} else if (color == BLACK) {
		return evaluationBlack[x][y];
	}
}

double getRookEvaluation(enum Color color, int x, int y)
{
	double evaluationWhite[][] = {
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0}
	};
	double evaluationBlack[][] = {
		{0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	};
	if (color == WHITE) {
		return evaluationWhite[x][y];
	} else if (color == BLACK) {
		return evaluationBlack[x][y];
	}
}

double getBishopEvaluation(enum Color color, int x, int y)
{
	double evaluationWhite[][] = {
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
		{-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
		{-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
		{-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
		{-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
	};
	double evaluationBlack[][] = {
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
		{-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
		{-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
		{-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
		{-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
		{-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
	};
	if (color == WHITE) {
		return evaluationWhite[x][y];
	} else if (color == BLACK) {
		return evaluationBlack[x][y];
	}
}

double getKnightEvaluation(enum Color color, int x, int y)
{
	double evaluation[][] = {
		{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
		{-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
		{-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
		{-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
		{-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
		{-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
		{-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
		{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
	};
	return evaluation[x][y];
}

double getQueenEvaluation(enum Color, int x, int y)
{
	double evaluation[][] = {
		{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
	};
	return evaluation[x][y];
}

double getKingEvaluation(enum Color color, int x, int y)
{
	double evaluationWhite[][] = {
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
		{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
		{2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
		{2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}
	};
	double evaluationBlack[][] = {
		{2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0},
		{2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
		{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
		{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}
	};
	if (color == WHITE) {
		return evaluationWhite[x][y];
	} else if (color == BLACK) {
		return evaluationBlack[x][y];
	}
}

double getPieceValue(int piece, int x, int y)
{
	switch (piece) {
		case PAWN_BLACK:
			return PAWN_VALUE + getPawnEvaluation(BLACK, x, y);
		case PAWN_WHITE:
			return -(PAWN_VALUE + getPawnEvaluation(WHITE, x, y));
		case ROOK_BLACK:
			return ROOK_VALUE + getRookEvaluation(BLACK, x, y);
		case ROOK_WHITE:
			return -(ROOK_VALUE + getRookEvaluation(WHITE, x, y));
		case KNIGHT_BLACK:
			return KNIGHT_VALUE + getKnightEvaluation(BLACK, x, y);
		case KNIGHT_WHITE:
			return -(KNIGHT_VALUE + getKnightEvaluation(WHITE, x, y));
		case BISHOP_BLACK:
			return BISHOP_VALUE + getBishopEvaluation(BLACK, x, y);
		case BISHOP_BLACK:
			return -(BISHOP_VALUE + getBishopEvaluation(WHITE, x, y));
		case QUEEN_BLACK:
			return QUEEN_VALUE + getQueenEvaluation(BLACK, x, y);
		case QUEEN_WHITE:
			return -(QUEEN_VALUE + getQueenEvaluation(WHITE, x, y));
		case KING_BLACK:
			return KING_VALUE + getKingEvaluation(BLACK, x, y);
		case KING_WHITE:
			return -(KING_VALUE + getKingEvaluation(WHITE, x, y));
	}
}

double getBoardUtility(int **matrix)
{
	int i, j, piece;
	double value = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			piece = matrix[i][j];
			if (piece != EMPTY_QUAD) {
				value += getPieceValue(piece, i, j);
			}
		}
	}
	return value;
}

double max(double num1, double num2)
{
	return (num1 > num2) ? num1 : num2;
}

double min(double num1, double num2)
{
	return (num1 > num2) ? num2 : num1;
}

double minimax(struct Node *node, bool isMaximize, double alpha, double beta)
{
	if (node->child != NULL) {
		if (isMaximize) {
			double max = -999999;
			struct Node *child = node->child;
			double value;
			while (child != NULL) {
				value = minimax(child, false, alpha, beta);
				if (value > max) {
					max = value;
				}
				alpha = max(alpha, max);
				if (beta <= alpha) {
					break;
				}
				child = child->next;
			}
			return max;
		} else {
			double min = 999999;
			struct Node *child = node->child;
			double value;
			while (child != NULL) {
				value = minimax(child, true, alpha, beta);
				if (value < min) {
					min = value;
				}
				beta = min(beta, min)
				if (beta <= alpha) {
					break;
				}
				child = child->next;
			}
			return min;
		}
	} else {
		return getBoardUtility(node->data);
	}
}

int maximizeFirst(struct Node *tree, double alpha, double beta)
{
	double max = -999999;
	int index = -1;
	struct Node *child = tree->child;
	double value;
	int i = 0;
	while (child != NULL) {
		value = minimax(child, false, alpha, beta);
		if (value > max) {
			max = value;
			index = i;
		}
		alpha = max(alpha, max);
		if (beta <= alpha) {
			break;
		}
		i++;
		child = child->next;
	}
	return index;
}