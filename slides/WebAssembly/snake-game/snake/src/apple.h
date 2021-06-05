#ifndef APPLE
#define APPLE

static const int DEFAULT_APPLE_WIDTH = 20;
static const int DEFAULT_APPLE_HEIGHT = 20;

void render_apple(void);
void generate_new_apple_pos(void);

int get_apple_posX(void);
int get_apple_posY(void);

#endif