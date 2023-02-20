#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <stdbool.h>
#include "definitions.h"
#include "move.h"

bool isPieceWhite(int piece);
bool isPieceBlack(int piece);
bool hasPiece(int **matrix, enum Color color, int x, int y);
struct Move* getPawnMoves(int **matrix, enum Color color, int x, int y);
struct Move* getRookMoves(int **matrix, enum Color color, int x, int y);
struct Move* getBishopMoves(int **matrix, enum Color color, int x, int y);
struct Move* getKnightMoves(int **matrix, enum Color color, int x, int y);
struct Move* getQueenMoves(int **matrix, enum Color color, int x, int y);
struct Move* getKingMoves(int **matrix, enum Color color, int x, int y);

#endif