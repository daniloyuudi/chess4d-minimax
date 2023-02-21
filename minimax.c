#include "minimax.h"
#include <stdlib.h>
#include "constants.h"
#include "math.h"

static const double pawnEvaluationWhite[][8] = {
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
	{1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
	{0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
	{0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
	{0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
	{0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
};

static const double pawnEvaluationBlack[][8] = {
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
	{0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
	{0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
	{0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
	{1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
	{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
};

static const double rookEvaluationWhite[][8] = {
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0}
};

static const double rookEvaluationBlack[][8] = {
	{0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
	{0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
};

static const double bishopEvaluationWhite[][8] = {
	{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
	{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
	{-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
	{-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
	{-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
	{-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
	{-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
	{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
};

static const double bishopEvaluationBlack[][8] = {
	{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
	{-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
	{-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
	{-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
	{-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
	{-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
	{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
	{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
};

static const double knightEvaluationWhite[][8] = {
	{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
	{-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
	{-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
	{-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
	{-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
	{-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
	{-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
	{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
};

static const double knightEvaluationBlack[][8] = {
	{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
	{-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
	{-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
	{-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
	{-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
	{-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
	{-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
	{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
};

static const double queenEvaluationWhite[][8] = {
	{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
	{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
	{-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
	{-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
	{0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
	{-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
	{-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
	{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
};

static const double queenEvaluationBlack[][8] = {
	{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
	{-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
	{-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
	{0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
	{-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
	{-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
	{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
	{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
};

static const double kingEvaluationWhite[][8] = {
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
	{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
	{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
	{2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
	{2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}
};

static const double kingEvaluationBlack[][8] = {
	{2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0},
	{2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
	{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
	{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
	{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}
};

double getPawnEvaluation(enum Color color, int x, int y)
{
	if (color == WHITE) {
		return pawnEvaluationWhite[x][y];
	} else if (color == BLACK) {
		return pawnEvaluationBlack[x][y];
	}
}

double getRookEvaluation(enum Color color, int x, int y)
{
	if (color == WHITE) {
		return rookEvaluationWhite[x][y];
	} else if (color == BLACK) {
		return rookEvaluationBlack[x][y];
	}
}

double getBishopEvaluation(enum Color color, int x, int y)
{
	if (color == WHITE) {
		return bishopEvaluationWhite[x][y];
	} else if (color == BLACK) {
		return bishopEvaluationBlack[x][y];
	}
}

double getKnightEvaluation(enum Color color, int x, int y)
{
	if (color == WHITE) {
		return knightEvaluationWhite[x][y];
	} else if (color == BLACK) {
		return knightEvaluationBlack[x][y];
	}
}

double getQueenEvaluation(enum Color color, int x, int y)
{
	if (color == WHITE) {
		return queenEvaluationWhite[x][y];
	} else if (color == BLACK) {
		return queenEvaluationBlack[x][y];
	}
}

double getKingEvaluation(enum Color color, int x, int y)
{
	if (color == WHITE) {
		return kingEvaluationWhite[x][y];
	} else if (color == BLACK) {
		return kingEvaluationBlack[x][y];
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
		case BISHOP_WHITE:
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

double minimax(struct Node *node, bool isMaximize, double alpha, double beta)
{
	if (node->child != NULL) {
		if (isMaximize) {
			double maxValue = -999999;
			struct Node *child = node->child;
			double value;
			while (child != NULL) {
				value = minimax(child, false, alpha, beta);
				if (value > maxValue) {
					maxValue = value;
				}
				alpha = max(alpha, maxValue);
				if (beta <= alpha) {
					break;
				}
				child = child->next;
			}
			return maxValue;
		} else {
			double minValue = 999999;
			struct Node *child = node->child;
			double value;
			while (child != NULL) {
				value = minimax(child, true, alpha, beta);
				if (value < minValue) {
					minValue = value;
				}
				beta = min(beta, minValue);
				if (beta <= alpha) {
					break;
				}
				child = child->next;
			}
			return minValue;
		}
	} else {
		return getBoardUtility(node->data);
	}
}

int maximizeFirst(struct Node *tree, double alpha, double beta)
{
	double maxValue = -999999;
	int index = -1;
	struct Node *child = tree->child;
	double value;
	int i = 0;
	while (child != NULL) {
		value = minimax(child, false, alpha, beta);
		if (value > maxValue) {
			maxValue = value;
			index = i;
		}
		alpha = max(alpha, maxValue);
		if (beta <= alpha) {
			break;
		}
		i++;
		child = child->next;
	}
	return index;
}