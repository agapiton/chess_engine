#include "chessboard.h"

void printboard(position *pos){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            printf("%d ",pos->board[i][j]);
        }
        printf("\n");
    }
}

position *cppos(position* pos){
    position *copiedpos = malloc(sizeof(position));
    copiedpos->toMove = pos->toMove;
    for(int i = 0; i < 8;i++){
        for (int j = 0; j < 8; j++){
            copiedpos->board[i][j] = pos->board[i][j];
        }
    }
    return copiedpos;
}

position *movepiece(position *pos, char* move){
    int piecetomove = PAWN;
    int rowto = 0;
    int columnto = 0;
    int rowfrom = 0;
    int columnfrom = 0;
    int i = 0;
    if (move[0] <= 'Z' && move[0] >= 'A'){
        i++;
        switch (move[0])
        {
        case 'N':
            piecetomove = KNIGHT;
            break;
        case 'B':
            piecetomove = BISHOP;
            break;
        case 'Q':
            piecetomove = QUEEN;
            break;
        case 'K':
            piecetomove = KING;
            break;
        case 'R':
            piecetomove = ROOK;
            break;
        default:
            fprintf(stderr, "ERROR: can not read a piece from move:%s", move);
            break;
        }
    }
    for(;!iscntrl(move[i]);i++){
        if(move[i] <= 'z' && move[i] >= 'a'){
            columnto = move[i] - 'a';
        }else if(move[i] <= '8' && move[i] >= '1'){
            rowto = '8' - move[i];
        }
        else if(move[i] == 'x'){
            columnfrom = columnto;
            rowfrom = rowto;
        }
    }
    position *copiedpos = cppos(pos);
    copiedpos->board[rowto][columnto] = piecetomove;
    return copiedpos;
}
