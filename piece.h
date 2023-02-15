#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <stdbool.h>
#include "definitions.h"
#include "move.h"

bool isPieceWhite(enum Piece piece);
bool isPieceBlack(enum Piece piece);
bool hasPiece(int **matrix, enum Color color, int x, int y);
struct Move* getPawnMoves(int **matrix, enum Color color, int x, int y);
struct Move* getRookMoves(int **matrix, enum Color color, int x, int y);
int max(int num1, int num2);
int min(int num1, int num2);
struct Move* getBishopMoves(int **matrix, enum Color color, int x, int y);
struct Move* getKnightMoves(int **matrix, enum Color color, int x, int y);
struct Move* getQueenMoves(int **matrix, enum Color color, int x, int y);
struct Move* getKingMoves(int **matrix, enum Color color, int x, int y);

#endif