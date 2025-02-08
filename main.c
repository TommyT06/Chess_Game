#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pieces.h"
#include "king.h"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;

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

static int white = 1;

static float board_xcoor[9];
static float board_ycoor[9];

static int clicked = 0;

static int last_board_index_x;
static int last_board_index_y;



#define r_b 139
#define g_b 69
#define b_b 19

#define r_w 255
#define g_w 218
#define b_w 185


void RenderScreen(int clicked);


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){
    int i;



    SDL_SetAppMetadata("Chess Board", "1.0", "com.example.renderer-points");

    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)){
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetWindowResizable(window, true);

    RenderScreen(0);
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    if (event->type == SDL_EVENT_QUIT) {
        return  SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        float mouse_x_pos = 0;
        float mouse_y_pos = 0;
        int board_index_x = 0;
        int board_index_y = 0;
        
        SDL_GetMouseState(&mouse_x_pos, &mouse_y_pos);

        if (mouse_x_pos <= board_xcoor[8] && mouse_y_pos <= board_ycoor[8] && mouse_x_pos >= board_xcoor[0] && mouse_y_pos >= board_ycoor[0]){


            if (mouse_x_pos >= board_xcoor[0] && mouse_x_pos < board_xcoor[1]){
                board_index_x = 0;
            }
            else if (mouse_x_pos >= board_xcoor[1] && mouse_x_pos < board_xcoor[2]){
                board_index_x = 1;
            }
            else if (mouse_x_pos >= board_xcoor[2] && mouse_x_pos < board_xcoor[3]){
                board_index_x = 2;
            }
            else if (mouse_x_pos >= board_xcoor[3] && mouse_x_pos < board_xcoor[4]){
                board_index_x = 3;
            }
            else if (mouse_x_pos >= board_xcoor[4] && mouse_x_pos < board_xcoor[5]){
                board_index_x = 4;
            }
            else if (mouse_x_pos >= board_xcoor[5] && mouse_x_pos < board_xcoor[6]){
                board_index_x = 5;
            }
            else if (mouse_x_pos >= board_xcoor[6] && mouse_x_pos < board_xcoor[7]){
                board_index_x = 6;
            }
            else if (mouse_x_pos >= board_xcoor[7] && mouse_x_pos < board_xcoor[8]){
                board_index_x = 7;
            }

            if (mouse_y_pos >= board_ycoor[0] && mouse_y_pos < board_ycoor[1]){
                board_index_y = 0;
            }
            else if (mouse_y_pos >= board_ycoor[1] && mouse_y_pos < board_ycoor[2]){
                board_index_y = 1;
            }
            else if (mouse_y_pos >= board_ycoor[2] && mouse_y_pos < board_ycoor[3]){
                board_index_y = 2;
            }
            else if (mouse_y_pos >= board_ycoor[3] && mouse_y_pos < board_ycoor[4]){
                board_index_y = 3;
            }
            else if (mouse_y_pos >= board_ycoor[4] && mouse_y_pos < board_ycoor[5]){
                board_index_y = 4;
            }
            else if (mouse_y_pos >= board_ycoor[5] && mouse_y_pos < board_ycoor[6]){
                board_index_y = 5;
            }
            else if (mouse_y_pos >= board_ycoor[6] && mouse_y_pos < board_ycoor[7]){
                board_index_y = 6;
            }
            else if (mouse_y_pos >= board_ycoor[7] && mouse_y_pos < board_ycoor[8]){
                board_index_y = 7;
            }
        
            if (clicked == 1){
                if (piece(init_pos, last_board_index_x, last_board_index_y, board_index_x, board_index_y)){

                    if ((isupper(init_pos[board_index_y][board_index_x]) && islower(init_pos[last_board_index_y][last_board_index_x]))
                    || (islower(init_pos[board_index_y][board_index_x]) && isupper(init_pos[last_board_index_y][last_board_index_x])
                    ) || init_pos[board_index_y][board_index_x] == '.'){

                        char temp_dest = init_pos[board_index_y][board_index_x];
                        char temp_init = init_pos[last_board_index_y][last_board_index_x];
                        init_pos[board_index_y][board_index_x] = init_pos[last_board_index_y][last_board_index_x];
                        init_pos[last_board_index_y][last_board_index_x] = '.';
                        if (check(init_pos, white)){
                            printf("Check");
                            init_pos[board_index_y][board_index_x] = temp_dest;
                            init_pos[last_board_index_y][last_board_index_x] = temp_init;
                        }
                        else{
                            if (white == 1){
                                white = 0;
                            }
                            else{
                                white = 1;
                            }
                        }
                    }
                }

                clicked = 0;
            }
            else if (init_pos[board_index_y][board_index_x] != '.'){
                if (white == 1){
                    if (isupper(init_pos[board_index_y][board_index_x])){
                        last_board_index_x = board_index_x;
                        last_board_index_y = board_index_y;              

                        clicked = 1;
                    }
                }
                else{
                    if (islower(init_pos[board_index_y][board_index_x])){
                        last_board_index_x = board_index_x;
                        last_board_index_y = board_index_y;              

                        clicked = 1;
                    }
                }
            }
        }

        else {
            clicked = 0;
        }

        RenderScreen(clicked);
    }


    if (event->type == SDL_EVENT_WINDOW_RESIZED){
        //printf("Change\n");
        RenderScreen(clicked);
    }

    return SDL_APP_CONTINUE;
}



void RenderScreen(int clicked){

    //initialize width and height of window
    int w;
    int h;

    SDL_GetWindowSize(window, &w, &h);

    // Calculate Square size and board margins
    int square_h = (h - (h * 0.1)) / 8;
    int w_offset = (w - (8*square_h)) / 2;

    // Clear screen and set starting draw colour
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, r_w, g_w, b_w, UINT8_MAX);


    /*
    Grab PNGs of pieces 
    should prob stor these globally someway but ill figure that out later
    */
    SDL_Texture* b_pawn = IMG_LoadTexture(renderer, "black-pawn.png");
    SDL_Texture* w_pawn = IMG_LoadTexture(renderer, "white-pawn.png");
    SDL_Texture* w_rook = IMG_LoadTexture(renderer, "white-rook.png");
    SDL_Texture* b_rook = IMG_LoadTexture(renderer, "black-rook.png");
    SDL_Texture* b_knight = IMG_LoadTexture(renderer, "black-knight.png");
    SDL_Texture* w_knight = IMG_LoadTexture(renderer, "white-knight.png");
    SDL_Texture* b_bishop = IMG_LoadTexture(renderer, "black-bishop.png");
    SDL_Texture* w_bishop = IMG_LoadTexture(renderer, "white-bishop.png");
    SDL_Texture* w_queen = IMG_LoadTexture(renderer, "white-queen.png");
    SDL_Texture* b_queen = IMG_LoadTexture(renderer, "black-queen.png");
    SDL_Texture* b_king = IMG_LoadTexture(renderer, "black-king.png");
    SDL_Texture* w_king  = IMG_LoadTexture(renderer, "white-king.png");
    SDL_Texture* current = NULL;


    //Render board with pieces on it row by row
    // (or maybe it does it column by column idek anymore)


    for (int i = 0; i < 8; i++){
        Uint8 r;

        //  swaps colour
        // swap is needed in both for loops so that the colour swaps on each new row
        SDL_GetRenderDrawColor(renderer, &r, NULL, NULL, NULL);
        if (r == r_w) {
                SDL_SetRenderDrawColor(renderer, r_b, g_b, b_b, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, r_w, g_w, b_w, 255);
            }
        for (int j = 0; j < 8; j++){
            SDL_FRect rect = {w_offset+(j*square_h),(h*0.05)+(i*square_h), square_h, square_h};

            board_xcoor[j] = w_offset + (j*square_h);
            board_ycoor[i] = (h*0.05)+(i*square_h);

            Uint8 r;

            SDL_GetRenderDrawColor(renderer, &r, NULL, NULL, NULL);
            if (r == r_w) {
                SDL_SetRenderDrawColor(renderer, r_b, g_b, b_b, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, r_w, g_w, b_w, 255);
            }

            if (i == last_board_index_y && j == last_board_index_x && clicked == 1){
                Uint8 r,g,b;
                SDL_GetRenderDrawColor(renderer, &r, &g, &b, NULL);
                SDL_SetRenderDrawColor(renderer, 255, 211, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            }
            else{
                SDL_RenderFillRect(renderer, &rect); 
            }

            if (init_pos[i][j] != '.'){
                switch (init_pos[i][j]){
                    case 'p':
                        current = b_pawn;
                        break;
                    case 'P':
                        current = w_pawn;
                        break;
                    case 'R':
                        current = w_rook;
                        break;
                    case 'r':
                        current = b_rook;
                        break;
                    case 'n':
                        current = b_knight;
                        break;
                    case 'N':
                        current = w_knight;
                        break;
                    case 'b':
                        current = b_bishop;
                        break;
                    case 'B':
                        current = w_bishop;
                        break;
                    case 'Q':
                        current = w_queen;
                        break;
                    case 'q':
                        current = b_queen;
                        break;
                    case 'k':
                        current = b_king;
                        break;
                    case 'K':
                        current = w_king;
                        break;
                    default:
                        printf("Error");
                }
                SDL_SetTextureBlendMode(current, SDL_BLENDMODE_BLEND);
                SDL_SetTextureScaleMode(current, SDL_SCALEMODE_LINEAR);

                SDL_RenderTexture(renderer, current, NULL, &rect);
            }
        }
    }


    board_xcoor[8] = board_xcoor[7] + square_h;
    board_ycoor[8] = board_ycoor[7] + square_h;

    //system("clear");
    // for (int i = 0; i < 8; i++){
    //         printf("%f %f\n", board_xcoor[i], board_ycoor[i]);
    // }
    
    SDL_RenderPresent(renderer);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){

}

SDL_AppResult SDL_AppIterate(void *appstate){
    return SDL_APP_CONTINUE;
}