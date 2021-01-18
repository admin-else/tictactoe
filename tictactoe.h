#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#define GET(board, input) (board[2 - (((input) -1) / 3)][((input) -1) % 3])

enum Sign {
	NONE   = ' ',
	CIRCLE = 'O',
	CROSS  = 'X',
};

int clear_stdin();

#endif
