#include <stdio.h>
#include "chessboard.h"



int main(int argc, char *argv[]){
    position *pos = &DEFAULT_STARTING_POSITION;
    char move[MAX_AN_MOVE_LEN+1] = "\0";
    do{
        pos = movepiece(pos, move);
        printboard(pos);
    }while(fgets(move, MAX_AN_MOVE_LEN, stdin));
    return 0;
}
