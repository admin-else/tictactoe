#!/bin/sh
cd "$(dirname "$0")" || exit 1

game1="1 4 2 5 3"
game2="5 8 9 1 3 6 7"
input="$game1 J $game2 N"

printf '%s\n' $input | make -f Makefile run
