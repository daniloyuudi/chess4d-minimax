#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "definitions.h"

struct Move* newMove(int x, int y);
void insertMove(struct Move **list, struct Move *move);
void freeMoveList(struct Move **list);
void printMoves(struct Move **list);

#endif