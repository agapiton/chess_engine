#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NUMBEROFPIECES 6
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
    char lastMove[MAX_AN_MOVE_LEN+1];
    uint8_t blackKingMoved: 1;
    uint8_t whiteKingMoved: 1;
    uint8_t longBlackRookMoved: 1;
    uint8_t longWhiteRookMoved: 1;
    uint8_t shortBlackRookMoved: 1;
    uint8_t shortWhiteRookMoved: 1;
}position;

typedef struct{
    int8_t pieceToMove;
    int8_t rowTo :4;
    int8_t columnTo :4;
    int8_t rowFrom :4;
    int8_t columnFrom :4;
    enum {
        NOTCASTLE,
        OO,
        OOO
    } isCastle;
}parsedMove;

extern const int8_t navmesh[NUMBEROFPIECES+1][8][2];

#define DEFAULT_STARTING_POSITION (position){\
    .board = DEFAULT_STARTING_BOARD,\
    .toMove = WHITE,                \
    .blackKingMoved = 0,\
    .whiteKingMoved = 0,\
    .longBlackRookMoved = 0,\
    .longWhiteRookMoved = 0,\
    .shortBlackRookMoved = 0,\
    .shortWhiteRookMoved = 0,\
}                                   

parsedMove parseMove(char*);

void printboard(position);

position movepiece(position, parsedMove);

uint8_t isCheck(position, int);