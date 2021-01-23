#include "input_players.h"

#include "tictactoe.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_input_next_free_space(enum Sign board[3][3], const enum Sign sign) {
	for (int i = 1; i <= 9; ++i) {
		if (GET(board, i) == NONE) {
			printf("*[%c]: %d\n", sign, i);
			return i;
		}
	}
	return 0;
}



int get_input_complete_row(enum Sign b[3][3], const enum Sign sign) {
	const enum Sign other = (sign == CROSS) ? CIRCLE : CROSS;
	for (int i = 0; i < 3; ++i) {
		if (b[i][0] == other && b[i][1] == other && b[i][2] == NONE) { return GET_NUMPAD_NUM(i, 2); }
		if (b[i][0] == other && b[i][2] == other && b[i][1] == NONE) { return GET_NUMPAD_NUM(i, 1); }
		if (b[i][1] == other && b[i][2] == other && b[i][0] == NONE) { return GET_NUMPAD_NUM(i, 0); }

		if (b[0][i] == other && b[1][i] == other && b[2][i] == NONE) { return GET_NUMPAD_NUM(2, i); }
		if (b[0][i] == other && b[2][i] == other && b[1][i] == NONE) { return GET_NUMPAD_NUM(1, i); }
		if (b[1][i] == other && b[2][i] == other && b[0][i] == NONE) { return GET_NUMPAD_NUM(0, i); }
	}

	if (b[0][0] == other && b[1][1] == other && b[2][2] == NONE) { return GET_NUMPAD_NUM(2, 2); }
	if (b[0][0] == other && b[2][2] == other && b[1][1] == NONE) { return GET_NUMPAD_NUM(1, 1); }
	if (b[1][1] == other && b[2][2] == other && b[0][0] == NONE) { return GET_NUMPAD_NUM(0, 0); }

	if (b[0][2] == other && b[1][1] == other && b[2][0] == NONE) { return GET_NUMPAD_NUM(2, 0); }
	if (b[0][2] == other && b[2][0] == other && b[1][1] == NONE) { return GET_NUMPAD_NUM(1, 1); }
	if (b[1][1] == other && b[2][0] == other && b[0][2] == NONE) { return GET_NUMPAD_NUM(0, 2); }

	for (int i = 0; i < 3; ++i) {
		if (b[i][0] == sign && b[i][1] == sign && b[i][2] == NONE) { return GET_NUMPAD_NUM(i, 2); }
		if (b[i][0] == sign && b[i][2] == sign && b[i][1] == NONE) { return GET_NUMPAD_NUM(i, 1); }
		if (b[i][1] == sign && b[i][2] == sign && b[i][0] == NONE) { return GET_NUMPAD_NUM(i, 0); }

		if (b[0][i] == sign && b[1][i] == sign && b[2][i] == NONE) { return GET_NUMPAD_NUM(2, i); }
		if (b[0][i] == sign && b[2][i] == sign && b[1][i] == NONE) { return GET_NUMPAD_NUM(1, i); }
		if (b[1][i] == sign && b[2][i] == sign && b[0][i] == NONE) { return GET_NUMPAD_NUM(0, i); }
	}

	if (b[0][0] == sign && b[1][1] == sign && b[2][2] == NONE) { return GET_NUMPAD_NUM(2, 2); }
	if (b[0][0] == sign && b[2][2] == sign && b[1][1] == NONE) { return GET_NUMPAD_NUM(1, 1); }
	if (b[1][1] == sign && b[2][2] == sign && b[0][0] == NONE) { return GET_NUMPAD_NUM(0, 0); }

	if (b[0][2] == sign && b[1][1] == sign && b[2][0] == NONE) { return GET_NUMPAD_NUM(2, 0); }
	if (b[0][2] == sign && b[2][0] == sign && b[1][1] == NONE) { return GET_NUMPAD_NUM(1, 1); }
	if (b[1][1] == sign && b[2][0] == sign && b[0][2] == NONE) { return GET_NUMPAD_NUM(0, 2); }

	return get_input_random(b, sign);
}


int get_input_random(enum Sign board[3][3], const enum Sign sign){
	int ff = 0;
	int free = 0;
	for (int i = 1; i <= 9; ++i) {
		if (GET(board, i) == NONE) {
			free = i;
			++ff;
		}
	}

	if (ff == 0) { return 0; }
	if (ff == 1) { return free; }

	int r = 0;
	do { r = 1 + rand() / ((RAND_MAX + 1u) / 9); } while (GET(board, r) != NONE);

	return r;
}

int get_input_from_player(enum Sign board[3][3], const enum Sign sign) {
	int input = 0;
	while (true) {
		if (isatty(fileno(stdin))) { printf("[%c]: ", sign); }
		int retval = scanf("%d", &input);
		// The input stream is at EOF.
		if (retval == EOF) { return EOF; }
		clear_stdin();
		if (retval == 0) {
			puts("Bitte gebe eine Zahl am PIN-Feld unter 10 ein.");
			continue;
		}
		// Invalid input.
		if (!(1 <= input && input <= 9)) {
			puts("Bitte gebe eine Zahl am PIN-Feld ein.");
			continue;
		}
		const enum Sign oldsign = GET(board, input);
		if (oldsign != NONE) {
			printf("Hier steht schon %c.\n", oldsign);
			continue;
		}
		break;
	}

	return input;
}
