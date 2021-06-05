#include <SDL2/SDL.h>

#ifndef MAIN
#define MAIN

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Renderer *getRenderer();

void quit_game(void);
void set_freeze(bool);

#endif