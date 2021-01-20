#pragma once

#include "tictactoe.h"

int get_input_next_free_space(
    enum Sign board[3][3],
    const enum Sign sign
);

int get_input_random(
    enum Sign board[3][3],
    const enum Sign sign
);

int get_input_from_player(
    enum Sign board[3][3],
    const enum Sign sign
);
