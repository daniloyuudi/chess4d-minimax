#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "definitions.h"

struct Node* newNode(int **data);
void addChild(struct Node *parent, struct Node *child);
void freeChildNode(struct Node *node);
struct Move* getMoves(int **matrix, int piece, int x, int y);
void getBlackMoves(struct Node *node, int level);
void getWhiteMoves(struct Node *node, int level);
struct Node* generateTree(int **matrix, int depth);
void freeTree(struct Node *root);
int getTreeMaxDepth(struct Node *node);

#endif