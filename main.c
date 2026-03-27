#include <stdio.h>
#include "chessboard.h"



int main(int argc, char *argv[]){
    position pos = DEFAULT_STARTING_POSITION;
    char move[MAX_AN_MOVE_LEN+1] = "\0";
    while(fgets(move, MAX_AN_MOVE_LEN+1, stdin)){
        printboard((pos = movepiece(pos, parseMove(move))));
    }
    return 0;
}
