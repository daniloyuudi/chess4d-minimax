package.cpath = "./?.dll"
local minimax = require "minimax"

EMPTY_QUAD = 0
PAWN_WHITE = 1
PAWN_BLACK = 2
ROOK_WHITE = 3
ROOK_BLACK = 4
KNIGHT_WHITE = 5
KNIGHT_BLACK = 6
BISHOP_WHITE = 7
BISHOP_BLACK = 8
QUEEN_WHITE = 9
QUEEN_BLACK = 10
KING_WHITE = 11
KING_BLACK = 12
DEPTH = 3

local executeOnce = false

function love.load()
	-- create matrix
	board = {}
	for i = 1, 8 do
		board[i] = {}
	end
	-- load pieces
	board[1][1] = ROOK_BLACK
	board[2][1] = KNIGHT_BLACK
	board[3][1] = BISHOP_BLACK
	board[4][1] = QUEEN_BLACK
	board[5][1] = KING_BLACK
	board[6][1] = BISHOP_BLACK
	board[7][1] = KNIGHT_BLACK
	board[8][1] = ROOK_BLACK
	for i = 1, 8 do
		board[i][2] = PAWN_BLACK
	end
	board[1][8] = ROOK_WHITE
	board[2][8] = KNIGHT_WHITE
	board[3][8] = BISHOP_WHITE
	board[4][8] = QUEEN_WHITE
	board[5][8] = KING_WHITE
	board[6][8] = BISHOP_WHITE
	board[7][8] = KNIGHT_WHITE
	board[8][8] = ROOK_WHITE
	for i = 1, 8 do
		board[i][7] = PAWN_WHITE
	end
end

function love.update()
	if executeOnce == false then
		originX, originY, destinationX, destinationY = minimax.getNextMove(board, DEPTH)
		executeOnce = true
	end
end

function love.draw()
	love.graphics.print(originX, 200, 300)
	love.graphics.print(originY, 200, 350)
	love.graphics.print(destinationX, 200, 400)
	love.graphics.print(destinationY, 200, 450)
end