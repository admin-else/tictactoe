# Makefile

CC := gcc
WINCC := x86_64-w64-mingw32-gcc
CFLAGS := -Wall -Wextra -O2

tictactoe: tictactoe.c
	${CC} ${CFLAGS} -o $@ $^

tictactoe.exe: tictactoe.c
	${WINCC} ${CFLAGS} -o $@ $^

run: tictactoe
	./tictactoe

windows: tictactoe.exe

.PHONY: run windows
