#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#define GET(board, input) (board[2 - (((input) -1) / 3)][((input) -1) % 3])

enum Sign {
	NONE   = ' ',
	CROSS  = 'X',
	CIRCLE = 'O',
};

int clear_stdin();

#endif
