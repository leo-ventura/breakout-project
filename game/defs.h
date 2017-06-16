#ifndef DEFS_H
#define DEFS_H

#define ROWS 3
#define COLUMNS 6
#define true 1
#define false 0
#define BALL_WIDTH 15
#define BALL_HEIGHT 15
#define BLOCK_WIDTH 120
#define BLOCK_HEIGHT 40
#define BAR_WIDTH 120
#define BAR_HEIGHT 20
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 600

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
  SDL_Surface *image;
} BLOCK;

#endif
