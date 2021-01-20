# Makefile

CC := gcc
WINCC := x86_64-w64-mingw32-gcc
CFLAGS := -Wall -Wextra -O2
# lin mode: BUILD=build , win mode: BUILD=build_win
BUILD := build

ifeq (${BUILD}, build_win)
CC := ${WINCC}
endif

all: ${BUILD}/tictactoe

ifeq (${BUILD}, build_win)
run: all
	wine ${BUILD}/tictactoe.exe
else
run: all
	${BUILD}/tictactoe
endif

test: all
	sh test.sh

${BUILD}/tictactoe.o: tictactoe.c tictactoe.h input_players.h
	${CC} ${CFLAGS} -c -o $@ tictactoe.c

${BUILD}/input_players.o: input_players.c input_players.h tictactoe.h
	${CC} ${CFLAGS} -c -o $@ input_players.c

${BUILD}/tictactoe: ${BUILD}/tictactoe.o ${BUILD}/input_players.o
	${CC} ${CFLAGS} -o $@ $^

.PHONY: all run test
