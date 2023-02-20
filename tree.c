#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "piece.h"
#include "matrix.h"

struct Node* newNode(int **data)
{
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;
	node->child = NULL;
	return node;
}

void addChild(struct Node *parent, struct Node *child)
{
	if (parent->child == NULL) {
		parent->child = child;
		return;
	}
	struct Node *pointer = parent->child;
	while (pointer->next != NULL) {
		pointer = pointer->next;
	}
	pointer->next = child;
}

void freeChildNode(struct Node *node)
{
	struct Node *pointer = node->child;
	struct Node *next = NULL;
	while (pointer != NULL) {
		next = pointer->next;
		freeChildNode(pointer);
		pointer = next;
	}
	freeMatrix(node->data);
	free(node);
}

struct Move* getMoves(int **matrix, int piece, int x, int y)
{
	switch (piece) {
		case PAWN_WHITE:
			return getPawnMoves(matrix, WHITE, x, y);
		case PAWN_BLACK:
			return getPawnMoves(matrix, BLACK, x, y);
		case ROOK_WHITE:
			return getRookMoves(matrix, WHITE, x, y);
		case ROOK_BLACK:
			return getRookMoves(matrix, BLACK, x, y);
		case KNIGHT_WHITE:
			return getKnightMoves(matrix, WHITE, x, y);
		case KNIGHT_BLACK:
			return getKnightMoves(matrix, BLACK, x, y);
		case BISHOP_WHITE:
			return getBishopMoves(matrix, WHITE, x, y);
		case BISHOP_BLACK:
			return getBishopMoves(matrix, BLACK, x, y);
		case QUEEN_WHITE:
			return getQueenMoves(matrix, WHITE, x, y);
		case QUEEN_BLACK:
			return getQueenMoves(matrix, BLACK, x, y);
		case KING_WHITE:
			return getKingMoves(matrix, WHITE, x, y);
		case KING_BLACK:
			return getKingMoves(matrix, BLACK, x, y);
	}
}

void getBlackMoves(struct Node *node, int level)
{
	int i, j;
	int piece;
	int **newBoard;
	int destinationX, destinationY;
	struct Node *newChild = NULL, *child = NULL;
	struct Move *moves, *pointer;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			piece = node->data[i][j];
			if (isPieceBlack(piece)) {
				moves = getMoves(node->data, piece, i, j);
				pointer = moves;
				while (pointer != NULL) {
					newBoard = copyMatrix(node->data);
					destinationX = pointer->x;
					destinationY = pointer->y;
					movePiece(newBoard, i, j, destinationX, destinationY);
					newChild = newNode(newBoard);
					addChild(node, newChild);
					pointer = pointer->next;
				}
			}
		}
	}
	if (level-1 > 0) {
		child = node->child;
		while (child != NULL) {
			getWhiteMoves(child, level-1);
			child = child->next;
		}
	}
}

void getWhiteMoves(struct Node *node, int level)
{
	int i, j;
	int piece;
	int **newBoard;
	int destinationX, destinationY;
	struct Node *newChild = NULL, *child = NULL;
	struct Move *moves, *pointer;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			piece = node->data[i][j];
			if (isPieceWhite(piece)) {
				moves = getMoves(node->data, piece, i, j);
				pointer = moves;
				while (pointer != NULL) {
					newBoard = copyMatrix(node->data);
					destinationX = pointer->x;
					destinationY = pointer->y;
					movePiece(newBoard, destinationX, destinationY, i, j);
					newChild = newNode(newBoard);
					addChild(node, newChild);
					pointer = pointer->next;
				}
			}
		}
	}
	if (level-1 > 0) {
		child = node->child;
		while (child != NULL) {
			getBlackMoves(child, level-1);
			child = child->next;
		}
	}
}

struct Node* generateTree(int **matrix, int depth)
{
	struct Node *root = newNode(matrix);
	if (depth > 0) {
		getBlackMoves(root, depth);
	}
	return root;
}

void freeTree(struct Node *root)
{
	struct Node *pointer = root->child;
	struct Node *next = NULL;
	while (pointer != NULL) {
		next = pointer->next;
		freeChildNode(pointer);
		pointer = next;
	}
	// do not free matrix for root node
	free(root);
}

int getTreeMaxDepth(struct Node *node)
{
	if (node->child == NULL) {
		return 0;
	} else {
		struct Node *child = node->child;
		int max = 0;
		int maxDepth;
		while (child != NULL) {
			maxDepth = getTreeMaxDepth(child);
			if (maxDepth > max) {
				max = maxDepth;
			}
			child = child->next;
		}
		return max+1;
	}
}
