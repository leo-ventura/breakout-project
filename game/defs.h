#ifndef DEFS_H
#define DEFS_H

#define ROWS 10
#define COLUMNS 7
#define true 1
#define false 0
#define BALL_WIDTH 15
#define BALL_HEIGHT 15
#define BLOCK_WIDTH 100
#define BLOCK_HEIGHT 40
#define BAR_WIDTH 120
#define BAR_HEIGHT 20
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 600
#define WINDOW_WIDTH 940
#define WINDOW_HEIGHT 600
#define SELECT_WIDTH 32
#define RED 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3
#define PURPLE 4

typedef struct _OBJECT {
  double posX;
  double posY;
  double stepX;
  double stepY;
  SDL_Surface* image;
  int imgW;
  int imgH;
} OBJECT;

typedef struct _BLOCK {
  int posX;
  int posY;
  int blockW;
  int blockH;
  int resistance;
  int color;
  SDL_Surface *image;
} BLOCK;

typedef struct _PLAYER{
  int points;
  char name[20];
} PLAYER;

#endif
