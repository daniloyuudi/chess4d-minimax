#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#include "definitions.h"
#include <stdbool.h>

double getPawnEvaluation(enum Color color, int x, int y);
double getRookEvaluation(enum Color color, int x, int y);
double getBishopEvaluation(enum Color color, int x, int y);
double getKnightEvaluation(enum Color color, int x, int y);
double getQueenEvaluation(enum Color, int x, int y);
double getKingEvaluation(enum Color color, int x, int y);
double getPieceValue(int piece, int x, int y);
double getBoardUtility(int **matrix);
double minimax(struct Node *node, bool isMaximize, double alpha, double beta);
int maximizeFirst(struct Node *tree, double alpha, double beta);

#endif
