/*
  TICTACTOE BOARD
  +−−−+−−−+−−−+
  | X | O | X |
  +−−−+−−−+−−−+
  |   | X | O |
  +−−−+−−−+−−−+
  | O |   | X |
  +−−−+−−−+−−−+
*/

#include "tictactoe.h"

#include "input_players.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 32


void clear_board(enum Sign board[3][3]) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) { board[i][j] = NONE; }
	}
}

void print_board(enum Sign board[3][3]) {
	static const char *line_separator = "+===+===+===+";
	for (int r = 0; r < 3; ++r) {
		puts(line_separator);
		printf("| %c | %c | %c |\n", board[r][0], board[r][1], board[r][2]);
	}
	puts(line_separator);
}

int clear_stdin() {
	char   buf[BUFSIZE];
	size_t length = 0;
	do {
		if (!fgets(buf, BUFSIZE, stdin) || feof(stdin)) { return EOF; }
		length = strlen(buf);
	} while (!(length && buf[length - 1] == '\n'));
	return 0;
}

int handle_input(
	enum Sign board[3][3], const enum Sign sign,
	int (*player_one_func)(enum Sign board[3][3], const enum Sign sign),
	int (*player_two_func)(enum Sign board[3][3], const enum Sign sign)
) {
	// [X]: n
	int retval = 0;
	// FIXME: This function is currently able to edit board.
	if (sign == CROSS) {
		retval = player_one_func(board, sign);
	} else {
		retval = player_two_func(board, sign);
	}

	if (retval == EOF) { return EOF; }
	if (!(1 <= retval && retval <= 9)) {
		fprintf(stderr, "Komischer fehler bei Spieler %c.\n", sign);
		return 1;
	}
	GET(board, retval) = sign;
	return 0;
}

/*
  TICTACTOE BOARD
  +−−−+−−−+−−−+
  | X | O | X |
  +−−−+−−−+−−−+
  |   | X | O |
  +−−−+−−−+−−−+
  | O |   | X |
  +−−−+−−−+−−−+
*/

enum Sign checkwin(enum Sign b[3][3]) {
	for (int i = 0; i < 3; ++i) {
		// Check for winning row.
		if (b[i][0] != NONE && b[i][0] == b[i][1] && b[i][0] == b[i][2]) {
			return b[i][0];
		}
		// Check for winnig column.
		if (b[0][i] != NONE && b[0][i] == b[1][i] && b[0][i] == b[2][i]) {
			return b[0][i];
		}
	}

	if (b[0][0] != NONE && b[0][0] == b[1][1] && b[0][0] == b[2][2]) {
		return b[0][0];
	}
	if (b[1][1] != NONE && b[1][1] == b[2][0] && b[0][2] == b[1][1]) {
		return b[1][1];
	}

	return NONE;
}

int play_game(enum Sign board[3][3], const bool is_multiplayer) {
	clear_board(board);
	print_board(board);
	int       turn   = 0;
	enum Sign player = CROSS;
	enum Sign winner = NONE;
	while (turn < 9 && winner == NONE) {
		int err = 0;
		if (is_multiplayer) {
			err = handle_input(
				board, player, &get_input_from_player, &get_input_from_player
			);
		} else {
			err = handle_input(
				board, player, &get_input_from_player, &get_input_next_free_space
			);
		}
		if (err == EOF) { return 1; }
		print_board(board);
		winner = checkwin(board);
		if (player == CIRCLE) {
			player = CROSS;
		} else {
			player = CIRCLE;
		}
		++turn;
	}

	switch (winner) {
	case NONE: puts("Niemand hat gewonnen."); break;
	case CIRCLE: puts("Kreis hat gewonnen."); break;
	case CROSS: puts("Kreuz hat gewonnen."); break;
	}
	return 0;
}

int main(const int argc, const char *const argv[]) {
	bool is_multiplayer = false;

	for (int arg = 0; arg < argc; ++arg) {
		if (strcmp(argv[arg], "-m") == 0) {
			is_multiplayer = true;
		}
	}

	enum Sign board[3][3];
	bool      play_again = true;
	while (play_again) {
		play_again    = 0;
		const int err = play_game(board, is_multiplayer);
		if (err) { return 1; }
		puts("Wenn sie noch einmal spielen wollen, geben sie 'J' ein.");
		if (isatty(fileno(stdin))) { printf("J / N: "); }
		char      chr;
		const int retval = scanf(" %c", &chr);
		if (retval == 1 && (chr == 'j' || chr == 'J')) { play_again = 1; }
	}

	return 0;
}

// (c) @Janfel & @Nomis
