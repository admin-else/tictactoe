#include "input_players.h"

#include "tictactoe.h"

#include <stdbool.h>
#include <stdio.h>
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
