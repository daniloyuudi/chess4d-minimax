#include <stdlib.h>
#include "tree.h"

struct Node* newNode(int **data)
{
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node->data = data;
	node->child = NULL;
	return node;
}

void insertNode(struct Node *parent, struct Node *child)
{
	if (parent->child == NULL) {
		parent->child = child;
		return;
	}
	struct Node *pointer = parent->child;
	while (pointer->child != NULL) {
		pointer = pointer->child;
	}
	pointer->child = child;
}

int** generateTree(int **matrix, int depth)
{
	struct Node *root = newNode(matrix);
	if (depth > 0) {
		//getMovesBlack(root, depth);
	}
}

