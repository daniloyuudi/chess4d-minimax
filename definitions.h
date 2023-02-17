#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

enum Piece
{
	PAWN_WHITE,
	PAWN_BLACK,
	ROOK_WHITE,
	ROOK_BLACK,
	KNIGHT_WHITE,
	KNIGHT_BLACK,
	BISHOP_WHITE,
	BISHOP_BLACK,
	QUEEN_WHITE,
	QUEEN_BLACK,
	KING_WHITE,
	KING_BLACK,
	EMPTY_QUAD
};

enum Color
{
	WHITE,
	BLACK,
	ANY_COLOR
};

struct Move
{
	int x, y;
	struct Move *next;
};

struct Node
{
	int **data;
	struct Node *next, *child;
};

struct MatrixDiff
{
	int originX, originY;
	int destinationX, destinationY;
};

#endif