#include <SDL2/SDL.h>
#include <stdbool.h>
#include "main.h"
#include "apple.h"

SDL_Rect apple;

void generate_new_apple_pos(void);

void render_apple()
{
    SDL_SetRenderDrawColor(getRenderer(), 226, 106, 106, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(getRenderer(), &apple);
}

void generate_new_apple_pos(void)
{
    apple.x = (rand() % (SCREEN_WIDTH - DEFAULT_APPLE_WIDTH + 1));
    apple.y = (rand() % (SCREEN_HEIGHT - DEFAULT_APPLE_HEIGHT + 1));
    apple.w = DEFAULT_APPLE_WIDTH;
    apple.h = DEFAULT_APPLE_HEIGHT;
}

int get_apple_posX(void)
{
    return apple.x;
}
int get_apple_posY(void)
{
    return apple.y;
}