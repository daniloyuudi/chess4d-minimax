#include <stdlib.h>
#include <stdio.h>
#include "move.h"

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