#include <SDL2/SDL.h>
#ifndef SNAKE
#define SNAKE

static const int DEFAULT_X = 500;
static const int DEFAULT_Y = 10;
static const int DEFAULT_WIDTH = 20;
static const int DEFAULT_HEIGHT = 20;

static const int DEFAULT_TAILS_N = 3;

struct TailNode{
    SDL_Rect rect;
    struct TailNode *next;
    struct TailNode *previous;
};

struct Snake{
    int dx;
    int dy;
    int size;
    struct TailNode head;
};

enum direction{LEFT, RIGHT, UP, DOWN};

bool init_snake(void);
void update_snake(void);
void change_snake_direction(int);
void free_tails(void);

#endif