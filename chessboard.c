#include "chessboard.h"

const int8_t navmesh[NUMBEROFPIECES+1][8][2] = {
[PAWN] = {{-1,0}},
[KNIGHT] = {{2,1},{2,-1},{1,2},{1,-2},{-1,2},{-1,-2},{-2,1},{-2,-1}},
[BISHOP] = {{1,1},{1,-1},{-1,1},{-1,-1}},
[ROOK] = {{1,0},{0,-1},{-1,0},{0,1}},
[KING] = {{1,1},{1,-1},{-1,1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1}},
[QUEEN] = {{1,1},{1,-1},{-1,1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1}}
};

void printboard(position pos){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            printf("%2d ",pos.board[i][j]);
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
        .isCastle = 0,
        .pieceToMove = PAWN
    };
    if(strcmp(move,"O-O-O")==0){
        movetoreturn.isCastle = OOO;
    }
    else if(strcmp(move,"O-O") == 0){
        movetoreturn.isCastle = OO;
    }else{
        movetoreturn.isCastle = NOTCASTLE;
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
        if(movetoreturn.columnFrom == -1 || movetoreturn.rowFrom == -1 ||\
        movetoreturn.columnTo == -1 || movetoreturn.rowTo == -1){
            fprintf(stderr,"ERROR: Unable to parse a move\n");
        }
    }
    return movetoreturn;
}



//PRBBL this function wouldnt be used anyway, buy now its debugged and working
uint8_t isCheck(position pos, int side){
    int kingrow;
    int kingcol;
    for(int i = 0; i<8;i++){
        for(int j = 0; j<8;j++){
            if(pos.board[i][j] == side*KING){
                kingcol = j;
                kingrow = i;
            }
        }
    }
    uint8_t result = 0;
    int k;
    // smth is wrong and it is not working yet. tomorrow i'll try learn debugging

    //CHECK FOR CHECK FROM PAWNS
    if(kingrow - side < 8 && kingrow - side >= 0){
        if(kingcol + 1 < 8 && kingcol + 1 >= 0){
            result += pos.board[kingrow - side][kingcol + 1] == PAWN * side * -1;
        }
        if(kingcol - 1 < 8 && kingcol - 1 >= 0){
            result += pos.board[kingrow - side][kingcol - 1] == PAWN * side * -1;
        }
    }

    //CHECK FOR CHECK FROM KNIGHT
    for(int i = 0;i<8;++i){
        if(kingrow+navmesh[KNIGHT][i][0] < 8 && kingrow+navmesh[KNIGHT][i][0] >= 0\
             && kingcol+navmesh[KNIGHT][i][1] < 8 && kingcol+navmesh[KNIGHT][i][1] >= 0\
            && pos.board[kingrow+navmesh[KNIGHT][i][0]][kingcol+navmesh[KNIGHT][i][1]] == KNIGHT * side * -1){
                result++;
        }
    }

    //CHECK FOR CHECK FROM BISHOP
    for(int i =0;i<4;++i){
        for(k = 1; kingrow+navmesh[BISHOP][i][0]*k < 8 && kingrow+navmesh[BISHOP][i][0]*k >= 0\
                && kingcol+navmesh[BISHOP][i][1]*k < 8 && kingcol+navmesh[BISHOP][i][1]*k >= 0\
                && pos.board[kingrow+k*navmesh[BISHOP][i][0]][kingcol+k*navmesh[BISHOP][i][1]] == EMPTY;++k);
        if(kingrow+navmesh[BISHOP][i][0]*k < 8 && kingrow+navmesh[BISHOP][i][0]*k >= 0\
            && kingcol+navmesh[BISHOP][i][1]*k < 8 && kingcol+navmesh[BISHOP][i][1]*k >= 0){
            result +=pos.board[kingrow+k*navmesh[BISHOP][i][0]][kingcol+k*navmesh[BISHOP][i][1]] == BISHOP * side * -1; 
        }
    }



    //CHECK FOR CHECK FROM ROOK
    for(int i =0;i<4;++i){
        for(k = 1; kingrow+navmesh[ROOK][i][0]*k < 8 && kingrow+navmesh[ROOK][i][0]*k >= 0\
                && kingcol+navmesh[ROOK][i][1]*k < 8 && kingcol+navmesh[ROOK][i][1]*k >= 0\
                && pos.board[kingrow+k*navmesh[ROOK][i][0]][kingcol+k*navmesh[ROOK][i][1]] == EMPTY;++k);
        if(kingrow+navmesh[ROOK][i][0]*k < 8 && kingrow+navmesh[ROOK][i][0]*k >= 0\
            && kingcol+navmesh[ROOK][i][1]*k < 8 && kingcol+navmesh[ROOK][i][1]*k >= 0){
            result +=pos.board[kingrow+k*navmesh[ROOK][i][0]][kingcol+k*navmesh[ROOK][i][1]] == ROOK * side * -1; 
        }
    }


    //CHECK FOR CHECK FROM QUEEN
    for(int i =0;i<8;++i){
        for(k = 1; kingrow+navmesh[QUEEN][i][0]*k < 8 && kingrow+navmesh[QUEEN][i][0]*k >= 0\
                && kingcol+navmesh[QUEEN][i][1]*k < 8 && kingcol+navmesh[QUEEN][i][1]*k >= 0\
                && pos.board[kingrow+k*navmesh[QUEEN][i][0]][kingcol+k*navmesh[QUEEN][i][1]] == EMPTY;++k);
        if(kingrow+navmesh[QUEEN][i][0]*k < 8 && kingrow+navmesh[QUEEN][i][0]*k >= 0\
            && kingcol+navmesh[QUEEN][i][1]*k < 8 && kingcol+navmesh[QUEEN][i][1]*k >= 0){
            result +=pos.board[kingrow+k*navmesh[QUEEN][i][0]][kingcol+k*navmesh[QUEEN][i][1]] == QUEEN * side * -1; 
        }
    }

    //CHECK FOR CHECK FROM KING
    for(int i = 0;i<8;++i){
        if(kingrow+navmesh[KING][i][0] < 8 && kingrow+navmesh[KING][i][0] >= 0\
             && kingcol+navmesh[KING][i][1] < 8 && kingcol+navmesh[KING][i][1] >= 0\
            && pos.board[kingrow+navmesh[KING][i][0]][kingcol+navmesh[KING][i][1]] == KING * side * -1){
                result++;
        }
    }
    return result;
}

position movepiece(position pos, parsedMove move){
    if(move.isCastle == NOTCASTLE && move.columnFrom != -1 && move.columnTo != -1 && move.rowFrom != -1 && move.rowTo != -1){
        pos.board[move.rowFrom][move.columnFrom] = EMPTY;
        pos.board[move.rowTo][move.columnTo] = move.pieceToMove * pos.toMove;
        return pos;
    }
    else if(move.isCastle == OO){
        return pos;
    }
    else if(move.isCastle == OOO){
        return pos;
    }
}
