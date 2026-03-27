#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_AN_MOVE_LEN 7

#define WHITE 1
#define BLACK -1

enum piece {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

typedef int8_t chessboard[8][8];

#define DEFAULT_STARTING_BOARD {                                                             \
    {BLACK*ROOK,BLACK*KNIGHT,BLACK*BISHOP,BLACK*QUEEN,BLACK*KING,BLACK*BISHOP,BLACK*KNIGHT,BLACK*ROOK},    \
    {BLACK*PAWN,BLACK*PAWN,BLACK*PAWN,BLACK*PAWN,BLACK*PAWN,BLACK*PAWN,BLACK*PAWN,BLACK*PAWN},             \
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},                                                     \
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},                                                     \
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},                                                     \
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},                                                     \
    {PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN,PAWN},                                                             \
    {ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK}                                                     \
}

typedef struct{
    int8_t toMove;
    chessboard board;
}position;

#define DEFAULT_STARTING_POSITION (position){\
    .board = DEFAULT_STARTING_BOARD,\
    .toMove = WHITE                 \
}                                   

void printboard(position*);

position *movepiece(position*, char*);

position *cppos(position*);