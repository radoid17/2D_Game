#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <algorithm>

int main(int argc, const char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("Platformer_v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 760, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* image;
    image = SDL_LoadBMP("Graphics/tiles.bmp");
    
    SDL_Surface* player;
    player = SDL_LoadBMP("Graphics/mario.bmp");
    SDL_Texture* player_texture = SDL_CreateTextureFromSurface(renderer, player);
    SDL_FreeSurface(player);


    SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    SDL_Rect r{32*8, 32*7, 64, 64};
    SDL_Event event;
    bool gameRunning = true;
    
    srand(time(NULL));
    int k = 0 %4 + 1;
    int tilemap[20][12] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, k, k, k}
    };
        
    SDL_Rect tile[20][12];
    for(int i = 0 ; i < 20 ; i ++){
        for(int j = 0 ; j < 12 ; j ++){
            tile[i][j].x = i * 32;
            tile[i][j].y = j * 32;
            tile[i][j].w = 32;
            tile[i][j].h = 32;
        }
    }

    SDL_Rect select_tile_1;
    select_tile_1.x = 0;
    select_tile_1.y = 0;
    select_tile_1.w = 32;
    select_tile_1.h = 32;

    SDL_Rect select_tile_2;
    select_tile_2.x = 32;
    select_tile_2.y = 0;
    select_tile_2.w = 32;
    select_tile_2.h = 32;

    SDL_Rect select_tile_3;
    select_tile_3.x = 0;
    select_tile_3.y = 32;
    select_tile_3.w = 32;
    select_tile_3.h = 32;

    SDL_Rect select_tile_4;
    select_tile_4.x = 32;
    select_tile_4.y = 32;
    select_tile_4.w = 32;
    select_tile_4.h = 32;


    while(gameRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameRunning = false;
            }
            else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                case SDLK_d: r.x += 32; break;
                case SDLK_a: r.x -= 32; break;
                case SDLK_w: r.y -= 32; break;
                case SDLK_s: r.y += 32; break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 3, 169, 244, 255);
        SDL_RenderClear(renderer);
        SDL_Delay(20);

        for(int i = 0 ; i < 20 ; i ++){
            for(int j = 0 ; j < 12 ; j ++){
                switch(tilemap[i][j]){
                    case 1: SDL_RenderCopy(renderer, tile_texture, &select_tile_1, &tile[i][j]); break;
                    case 2: SDL_RenderCopy(renderer, tile_texture, &select_tile_2, &tile[i][j]); break;
                    case 3: SDL_RenderCopy(renderer, tile_texture, &select_tile_3, &tile[i][j]); break;
                    case 4: SDL_RenderCopy(renderer, tile_texture, &select_tile_4, &tile[i][j]); break;
                }
            }
        }

        SDL_RenderCopy(renderer, player_texture, NULL, &r);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    return 0;
}