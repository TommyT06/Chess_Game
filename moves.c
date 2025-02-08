#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static char init_pos[8][8] = {
        'r','n','b','q','k','b','n','r',
        'p','p','p','p','p','p','p','p',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        'P','P','P','P','P','P','P','P',
        'R','N','B','Q','K','B','N','R'
    };

int check_diag(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y);
int check_str(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y);
int piece(char pos[][8], int cur_x, int cur_y , int dest_x, int dest_y){

    //printf("%c %c %d %d %d %d\n", pos[cur_y][cur_x], pos[dest_y][dest_x], cur_x, cur_y, dest_x, dest_y);
    int first;

    switch (pos[cur_y][cur_x]){

        case 'p':
            if (cur_y == 1){
                first = 1;
            }
            else{
                first = 0;
            }

            if (first == 1){
                if (cur_y + 1 == dest_y || cur_y + 2 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.' && pos[cur_y+1][cur_x] == '.'){
                            return 1;  
                        }
                    }
                }
            }
            else if (first == 0){
                if (cur_y + 1 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.'){
                            return 1;  
                        }
                    }
                }
            }

            if (cur_y + 1 == dest_y && (cur_x + 1 == dest_x || cur_x - 1 == dest_x)){
                if (pos[dest_y][dest_x] != '.'){
                    return 1;
                }
            }
            else{
                return 0;
            }

            break;
        case 'P':
            if (cur_y == 6){
                first = 1;
            }
            else{
                first = 0;
            }

            if (first == 1){
                if (cur_y - 1 == dest_y || cur_y - 2 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.' && pos[cur_y-1][cur_x] == '.'){
                            return 1;  
                        }
                    }
                }
            }
            else if (first == 0){
                if (cur_y - 1 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.'){
                            return 1;  
                        }
                    }
                }
            }


            if (cur_y - 1 == dest_y && (cur_x + 1 == dest_x || cur_x - 1 == dest_x)){

                if (pos[dest_y][dest_x] != '.'){
                    printf("Captured");
                    return 1;
                }
            }
            else{
                return 0;
            }
        break;
        case 'N':
        case 'n':
            if (abs(cur_x - dest_x) == 1 && abs(cur_y - dest_y) == 2){
                return 1;
            }
            if (abs(cur_x - dest_x) == 2 && abs(cur_y - dest_y) == 1){
                return 1;
            }
        break;

        case 'b':
        case 'B':
            if (check_diag(pos, cur_x, cur_y, dest_x, dest_y)){
                return 1;
            }
            else {
                return 0;
            }
        break;

        case 'r':
        case 'R':
            if (check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                return 1;
            }
            else {
                return 0;
            }
        break;
        case 'Q':
        case 'q':
            if (dest_x == cur_x || dest_y == cur_y){
                if (check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                    return 1;
                }
            }
            else {
                if (check_diag(pos, cur_x, cur_y, dest_x, dest_y)){
                    return 1;
                }
            }
            return 0;
        break;
        case 'k':
        case 'K':
            if (abs(dest_x-cur_x) <= 1 & abs(dest_y-cur_y) <= 1){
                return 1;
            }
            else {
                return 0;
            }
    }
    return 0;
}

int check_diag(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y){

    int i = 0;
    int j = 0;
    int dif_x = 0;
    int dif_y = 0;
    int x = 0;

    dif_x = abs(cur_x - dest_x);
    dif_y = abs(cur_y - dest_y);

    if (dif_x != dif_y){
        return 0;
    }

    if (dest_x > cur_x){
        i = 1;
    }
    else {
        i = -1;
    }

    if (dest_y > cur_y){
        j = 1;
    }
    else {
        j = -1;
    }
    printf("%d %d\n", cur_x, cur_y);
    for (x = 1; x < dif_x; x++){
        printf("%d %d\n", cur_x+(x*i), cur_y+(x*j));
        if (pos[cur_y+(x*j)][cur_x+(x*i)] != '.'){
            printf("Fail\n");
            return 0;
        }
    }
    printf("\n");


    return 1;
}

int check_str(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y){

    int vert = 0;
    int dif = 0;
    int i = 0 ;
    int opp = 1;

    if (cur_x == dest_x){
        vert = 1;
        dif = (dest_y - cur_y);
    }
    else {
        vert = 0;
        dif = (dest_x - cur_x);
    }

    if (dif < 0){
        opp = -1;
        dif = dif * -1;
    }

    if (vert == 0){
        for ( i = 1; i < dif; i++){
            if (pos[cur_y][cur_x+(i*opp)] != '.'){
                return 0;
            }
        }
    }
    else {
        for (i = 1; i<dif; i++){
            if (pos[cur_y+(i*opp)][cur_x] != '.'){
                return 0;
            }
        }
    }

    return 1;
    
}