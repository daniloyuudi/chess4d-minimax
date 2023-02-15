#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "definitions.h"

struct Node* newNode(int **data);
void insertNode(struct Node *parent, struct Node *child);
int** generateTree(int **matrix, int depth);

#endif