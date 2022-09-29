#include <stdio.h>
#include <stdbool.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "main.h"
#include "snake.h"
#include "apple.h"

void handle_events(void);
void quit(void);

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;

bool running = false;
bool frozen = false;

bool init(void)
{
    bool success = true;
    window = NULL;
    renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not be initiliazed. SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    window = SDL_CreateWindow("snake game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window){
        printf("SDL_Window could not be initialized. SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);    
    }

    if(!init_snake()){
        printf("snake could not be initialized.\n");
        success = false;
    }

    generate_new_apple_pos();

    running = true;
    return success;
}

void main_loop(void)
{
    handle_events();

    if(frozen)
        return;

    SDL_SetRenderDrawColor(renderer, 18, 1, 54, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    update_snake();
    render_apple();

    SDL_RenderPresent(renderer);

    SDL_Delay(70);  
}

int main(int argc, char* args[])
{
    if(!init())
        return -1;
    else{

        #ifdef __EMSCRIPTEN__
            emscripten_set_main_loop(main_loop, 0, 1);
        #endif

        #ifndef __EMSCRIPTEN__
            while(running)
                main_loop();
        #endif
    }
    
    quit_game();
    return 0;
}

void handle_events()
{
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            quit_game();
        }
        else if(e.type == SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_RIGHT:
                    change_snake_direction(RIGHT);
                    break;
                case SDLK_LEFT:
                    change_snake_direction(LEFT);
                    break;
                case SDLK_UP:
                    change_snake_direction(UP);
                    break;
                case SDLK_DOWN:
                    change_snake_direction(DOWN);
                    break;
            }
        }
    }
}

void quit_game(void)
{
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    free_tails();
    SDL_Quit();

    #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
    #endif
}

void set_freeze(bool b)
{
    frozen = b;
}

SDL_Renderer* getRenderer()
{ 
    return renderer; 
}