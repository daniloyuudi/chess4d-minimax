#include "definitions.h"
#include "matrix.h"
#include "tree.h"
#include "minimax.h"
#include "lua.h"
#include "lauxlib.h"

struct MatrixDiff getMatrixDiff(int **matrix1, int **matrix2)
{
	struct MatrixDiff diff;
	int i, j, piece1, piece2;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; ++) {
			piece1 = matrix1[i][j];
			piece2 = matrix2[i][j];
			if (piece1 != EMPTY_QUAD && isPieceBlack(piece1)
				&& piece2 == EMPTY_QUAD) {
					diff.originX = i;
					diff.originY = j;
			}
			if ((piece1 == EMPTY_QUAD || piece1 != EMPTY_QUAD
				&& isPieceWhite(piece1)) && piece2 != EMPTY_QUAD
				&& isPieceBlack(piece2)) {
					diff.destinationX = i;
					diff.destinationY = j;
			}
		}
	}
	return diff;
}

int** getMatrix(lua_State *L)
{
	int **matrix = newMatrix();
	int i, j, result;
	for (i = 1; i <= 8; i++) {
		lua_pushnumber(L, i);
		lua_gettable(L, -2);
		for (j = 1; j <= 8; j++) {
			lua_pushnumber(L, j);
			lua_gettable(L, -2);
			if (lua_isnumber(L, -1)) {
				error(L, "array value must be a number");
			}
			result = lua_tonumber(L, -1);
			matrix[i][j] = result;
			lua_pop(L, 1); // remove number
		}
		lua_pop(L, 1);
	}
	return matrix;
}

struct Node* getChild(struct Node *tree, int index)
{
	int i = 0;
	struct Node *child = tree->child;
	while (child != NULL) {
		if (i == index) {
			return child;
		}
		child = child->next;
		i++;
	}
}

int getNextMove(lua_State *L)
{
	if (!lua_isnumber(L, -1)) {
		error(L, "depth must be a number");
	}
	int depth = lua_tonumber(L, -1);
	lua_pop(L, 1);
	int **matrix = getMatrix(L);
	struct Node *tree = generateTree(matrix, depth);
	int index = maximizeFirst(tree, -999999, 999999);
	struct Node *selectedPath = getChild(tree,  index);
	MatrixDiff diff = getMatrixDiff(tree->data, selectedPath->data);
	lua_pushnumber(L, diff.originX);
	lua_pushnumber(L, diff.originY);
	lua_pushnumber(L, diff.destinationX);
	lua_pushnumber(L, diff.destinationY);
	return 4;
}

static const struct lual_Reg functions[] = {
	{"getNextMove", getNextMove}
};

int luaopen_hello(lua_State *L)
{
	luaL_register(L, "hello", functions);
	return 1;
}