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

// WIP
/*
int get_input_complete_row(enum Sign board[3][3], const enum Sign sign) {
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
*/

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
