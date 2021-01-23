#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#define GET(board, input) (board[2 - (((input) -1) / 3)][((input) -1) % 3])
#define GET_NUMPAD_NUM(row, col) ((col) + (3 * (2 - (row))) + 1)

enum Sign {
	NONE   = ' ',
	CROSS  = 'X',
	CIRCLE = 'O',
};

int clear_stdin();

#endif
