#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check_straight(char pos[][8], int , int, int , int , int);

int check(char pos[][8], int white){

    char king;
    if (white == 1){
        king = 'K';
    }
    else {
        king = 'k';
    }
    int i,j;
    int king_x;
    int king_y;

        for (i = 0; i < 8; i++){
            for (j = 0; j < 8; j++){
                if (pos[j][i] == king){
                    king_x = i;
                    king_y = j;
                } 
            }
        }

    if (white == 1){
        if (pos[king_y-1][king_x+1] == 'p' || pos[king_y-1][king_x-1] == 'p'){
            return 1;
        }
    }
    else {
        if (pos[king_y+1][king_x+1] == 'P' || pos[king_y+1][king_x-1] == 'P'){
            return 1;
        }
    }

    if (check_straight(pos, king_x, king_y, white, 1, 0)){
        return 1;
    }
    if (check_straight(pos, king_x, king_y, white, -1, 0)){
        return 1;
    }
    if (check_straight(pos, king_x, king_y, white, 0, 1)){
        return 1;
    }
    if (check_straight(pos, king_x, king_y, white, 0, -1)){
        return 1;
    }

    return 0;

}

int check_straight(char pos[][8], int king_x, int king_y, int white, int vert, int hor){

    while (king_x > 0 && king_y > 0 && king_x < 7 && king_y < 7){
        king_x = king_x + hor;
        king_y = king_y + vert;
        if (white == 1){
            if (pos[king_y][king_x] == 'r' || pos[king_y][king_x] == 'q'){
                return 1;
            }
            else if (isupper(pos[king_y][king_x])){
                return 0;
            }
        }
        else{
            if (pos[king_y][king_x] == 'R' || pos[king_y][king_x] == 'Q'){
                return 1;
            }
            else if ((islower(pos[king_y][king_x]))){
                return 0;
            }
        }
    }

    return 0;
}