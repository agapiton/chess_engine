#include "chessboard.h"

void printboard(position pos){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            printf("%d ",pos.board[i][j]);
        }
        printf("\n");
    }
}

parsedMove parseMove(char* move){
    int i = 0;
    parsedMove movetoreturn = {
        .columnFrom = -1,
        .rowFrom = -1,
        .columnTo = -1,
        .rowTo = -1,
        .pieceToMove = PAWN
    };
    if (move[0] <= 'Z' && move[0] >= 'A'){
        i++;
        switch (move[0])
        {
        case 'N':
            movetoreturn.pieceToMove = KNIGHT;
            break;
        case 'B':
            movetoreturn.pieceToMove = BISHOP;
            break;
        case 'Q':
            movetoreturn.pieceToMove = QUEEN;
            break;
        case 'K':
            movetoreturn.pieceToMove = KING;
            break;
        case 'R':
            movetoreturn.pieceToMove = ROOK;
            break;
        default:
            fprintf(stderr, "ERROR: can not read a piece from move:%s", move);
            break;
        }
    }
    /*DONT FORGET TO CHECK FOR CASTLE*/
    for(; !iscntrl(move[i]); i++){ //while move[i] is not an end of the string we check
        if(move[i] <= 'h' && move[i] >= 'a'){ // if the symbol is column
            movetoreturn.columnTo = move[i] - 'a';
        }
        else if(move[i] <= '8' && move[i] >= '1'){ // if the symbol is row
            movetoreturn.rowTo = '8' - move[i];
        }
        else if(move[i] == 'x'){ //or if it is declarates capture
            movetoreturn.columnFrom = movetoreturn.columnTo;
            movetoreturn.rowFrom = movetoreturn.rowTo;
            movetoreturn.rowTo = -1;
            movetoreturn.columnTo = -1;
        }
        //check for # and *
    }
    return movetoreturn;
}

position movepiece(position pos, parsedMove move){
    pos.board[move.rowTo][move.columnTo] = move.pieceToMove;
    return pos;
}
