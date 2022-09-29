#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "snake.h"
#include "main.h"
#include "apple.h"

struct Snake snake;
struct TailNode *lasttail;

void push_tail();

bool init_snake()
{
    // default direction
    snake.dx = -1;
    snake.dy = 0;

    // initializes head
    snake.head.rect.x = DEFAULT_X;
    snake.head.rect.y = DEFAULT_Y;
    snake.head.rect.w = DEFAULT_WIDTH;
    snake.head.rect.h = DEFAULT_HEIGHT;
    snake.head.next = NULL;
    snake.head.previous = NULL;

    // sets pointer of last tail to head
    lasttail = &snake.head;

    // pushes default tails
    for(int i = 0; i < DEFAULT_TAILS_N; ++i)
        push_tail();

    return true;
}


void render_tail(SDL_Rect *tail)
{   // renders individual parts of the snake
    SDL_SetRenderDrawColor(getRenderer(), 252, 191, 30, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(getRenderer(), tail);
}

void check_collision()
{
    // fruit collision
    if(abs(snake.head.rect.x - get_apple_posX()) < DEFAULT_WIDTH && abs(snake.head.rect.y - get_apple_posY()) < DEFAULT_HEIGHT){
        push_tail();
        generate_new_apple_pos();
    }

    // border collision
    if(snake.head.rect.x > SCREEN_WIDTH - DEFAULT_WIDTH)
        snake.head.rect.x = 0;
    else if(snake.head.rect.x < 0 - DEFAULT_WIDTH)
        snake.head.rect.x = SCREEN_WIDTH;
    else if(snake.head.rect.y < 0 - DEFAULT_HEIGHT)
        snake.head.rect.y = SCREEN_HEIGHT;
    else if(snake.head.rect.y > SCREEN_HEIGHT - DEFAULT_HEIGHT)
        snake.head.rect.y = 0;
}

void update_snake(void)
{   // iterates over the head and the tail
    for(struct TailNode *ptr = lasttail; ptr != NULL; ptr = (*ptr).previous){
        if((*ptr).previous == NULL){ // in other words, if this "tail" is the head
            snake.head.rect.x += snake.dx * DEFAULT_WIDTH;
            snake.head.rect.y += snake.dy * DEFAULT_HEIGHT;
        } else { // if it's the snake's body
            //if(abs(snake.head.rect.x - (*ptr).rect.x) < DEFAULT_WIDTH && // checks collision with the head
             //  abs(snake.head.rect.y - (*ptr).rect.y) < DEFAULT_HEIGHT)
               // quit_game();

            (*ptr).rect.x = (*ptr).previous->rect.x;
            (*ptr).rect.y = (*ptr).previous->rect.y;
        }

        render_tail(&(*ptr).rect);
    }

    check_collision(); // head-only collision (fruit, border, etc.)
}

void push_tail()
{   // pushes a new tail inside the linked list
    struct TailNode *new_tail = malloc(sizeof(struct TailNode));
    if(new_tail == NULL) 
        quit_game();

    (*new_tail).rect.w = DEFAULT_WIDTH;
    (*new_tail).rect.h = DEFAULT_HEIGHT;

    (*new_tail).next = NULL;
    (*new_tail).previous = lasttail;

    (*lasttail).next = new_tail;
    lasttail = new_tail;
}

void change_snake_direction(int dir)
{
    if(dir == RIGHT && snake.dx != -1){
        snake.dx = 1;
        snake.dy = 0;
    }
    else if(dir == LEFT && snake.dx != 1){
        snake.dx = -1;
        snake.dy = 0;
    }
    else if(dir == UP && snake.dy != 1){
        snake.dy = -1;
        snake.dx = 0;
    }
    else if(dir == DOWN && snake.dy != -1){
        snake.dy = 1;
        snake.dx = 0;
    }
}

void free_tails()
{
    struct TailNode *tmp;
    struct TailNode *secondtail;
    secondtail = snake.head.next; // we skip the first node (head) because it's allocated in the stack

    while(secondtail != NULL){
        tmp = secondtail;
        secondtail = (*secondtail).next;
        free(tmp);
    }
}