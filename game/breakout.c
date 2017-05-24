/* This is a version of the game Breakout developed by students from Federal
* University of Rio de Janeiro.
* Developers: Breno Coll, Breno Tostes and Leonardo Ventura
* Professor: Adriano Cruz
*/

/* Using SDL, SDL_image, stdio, strings and time*/
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define BLOCK_WIDHT 120
#define BLOCK_HEIGHT 40

#define ROWS 7
#define COLUMNS 3

#define BAR_WIDTH 120
#define BAR_HEIGHT 20

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 600

/*SDL_Surface* screen
SDL_Window* window;
SDL_Event event;*/


/* Constants */
const int true = 1;
const int false = 0;

const int BALL_WIDHT = 15;
const int BALL_HEIGHT = 15;

/* Defining structures */
typedef struct _BALL {
  int posX;
  int posY;
  int stepX;
  int stepY;
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

/* Global variables*/
OBJECT ball;

/* The window we'll be rendering to */
SDL_Window *gWindow = NULL;

/* Characters image */
/*OBJECT bar;*/

/* The surface contained by the window */
SDL_Surface *gScreenSurface = NULL;

/* The surface displaying the menu */
SDL_Surface *gMenuSurface = NULL;

/* Current displayed ball image */
SDL_Surface *gBallSurface = NULL;

/* blocks' surface */
SDL_Surface *gBlockSurface = NULL;

/* Functions prototypes */

/*Starts up SDL and creates window*/
int init();

/* menu function */
/*void menu();*/

/* Loads midia */
int loadMedia();

/* Frees midia e shuts down SDL */
void closing();

/* Loads individual image */
SDL_Surface* loadSurface(char *path);

/* Create object function */
OBJECT createOBJECT(int posX, int posY, int stepX, int stepY, SDL_Surface *image);

/* Move object function */
void moveOBJECT(OBJECT *p);

/* Create block function */
BLOCK createBLOCK(int posX, int posY, SDL_Surface *image);

/* function to draw blocks */
void drawBlock(BLOCK b, SDL_Rect srcBlock);

/* check collision between ball and block */
BLOCK collisionBlock(BLOCK block, OBJECT *ball, int i, int j);


/* starts main function */


int main(int argc, char const *argv[]) {
  /* local variables */
  SDL_Rect srcBall, dstBall;
  SDL_Rect srcBlock;
/*  SDL_Rect srcBar, dstBar;*/
  BLOCK block[ROWS][COLUMNS];
  int quit;
  int i, j;
  int qRows = 0, qColumns = 0;
  /* event handler */
  SDL_Event e;

  /* Start up SDL and create window */
  if (!init() || !loadMedia()) printf("SDL could not be initialized\n");

  /* MAIN MENU CODE HERE */
  /*menu();*/
  /* create ball object */
  ball = createOBJECT(SCREEN_WIDTH/2, ((3*SCREEN_HEIGHT/4) + 15), 0, 0, gBallSurface);
  /* create bar object */
/*  bar = createOBJECT(SCREEN_WIDTH/2, (3*SCREEN_HEIGHT/4), 0, 0, gBarSurface);*/

  /* counts how many rows and columns */
  for (i = 0; i*BLOCK_WIDHT < SCREEN_WIDTH; i++) qRows++;
  for (j = 0; j*BLOCK_HEIGHT < SCREEN_HEIGHT; j++) qColumns++;

  /* loop to create blocks */
  for (j = 0; j < qColumns/5; j++) {
    for (i = 0; i < qRows; i++) {
      block[i][j] = createBLOCK(BLOCK_WIDHT*i, BLOCK_HEIGHT*j, gBlockSurface);
    }
  }
  quit = false;

  while(!quit) {
    /* Starts game main loop */
    while(SDL_PollEvent(&e) != 0) {
      /* user request quit*/
      switch(e.type) {
        case SDL_QUIT:
          quit = true;
          break;
      case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_ESCAPE) {
              quit = true;
          }
          else if (e.key.keysym.sym == SDLK_SPACE) {
            ball.stepX = 1;
            ball.stepY = -1;
          }
          /*else if (e.key.keysym.sym == SDLK_LEFT) {
            bar.stepX = 1;
          }
          else if (e.key.keysym.sym == SDLK_RIGHT) {
            bar.stepX = -1;
          }*/
        break;
      }
            /* user taps left arrow */
           /*case SDLK_LEFT:
              bar.posX -= bar.stepX;
              break;*/
            /* user taps right arrow */
            /*case SDLK_RIGHT:
              bar.posX += bar.stepX;
              break;*/
    }
        /* Fill screen surface with white */
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));

    moveOBJECT(&ball);


    for (j = 0; j < qColumns/5; j++) {
      for (i = 0; i < qRows; i++) {
        block[i][j] = collisionBlock(block[i][j], &ball, i, j);
      }
    }

        /* ball's source */
    srcBall.x = 0;
    srcBall.y = 0;
    srcBall.w = 15;
    srcBall.h = 15;
    dstBall.x = ball.posX;
    dstBall.y = ball.posY;

    /* bar's source */
    /*srcBar.x = 0;
    srcBar.y = 0;
    srcBar.w = BAR_WIDTH;
    srcBar.h = BAR_HEIGHT;
    dstBar.x = bar.posX;
    dstBar.y = bar.posY;*/

    /* block's source */
    srcBlock.x = 0;
    srcBlock.y = 0;
    srcBlock.w = BLOCK_WIDHT;
    srcBlock.h = BLOCK_HEIGHT;

    for (j = 0; j < qColumns/5; j++) {
      for (i = 0; i < qRows; i++) {
        if (block[i][j].resistance > 0) drawBlock(block[i][j], srcBlock);
      }
    }

    if(SDL_BlitSurface(ball.image, &srcBall, gScreenSurface, &dstBall) < 0/* ||
      SDL_BlitSurface(bar.image, &srcBar, gScreenSurface, &dstBar) < 0*/) {
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        quit = true;
    }

    /* Update the surface */
    SDL_UpdateWindowSurface(gWindow);

    /* it'll be changed later */
    SDL_Delay(2.5);
    }

  closing();

  return 0;
}


/*void menu() {*/
/*  gMenuSurface = loadSurface(INSERT HOME PAGE'S BACKGROUNG PATH HERE);*/

  /* local variables */
  /*int quit = false;*/
  /* Event handler */
  /*SDL_Event e;*/
  /* CODE */
/*}*/


void drawBlock(BLOCK b, SDL_Rect srcBlock) {
  SDL_Rect dstRect;
  dstRect.x = b.posX;
  dstRect.y = b.posY;
  SDL_BlitSurface(b.image, &srcBlock, gScreenSurface, &dstRect);
}

BLOCK createBLOCK(int posX, int posY, SDL_Surface *image) {
  BLOCK b;
  b.posX = posX;
  b.posY = posY;
  b.resistance = 1;
  b.image = image;
  return b;
}

BLOCK collisionBlock(BLOCK block, OBJECT *ball, int i, int j) {
  /*left = ball.posX <= block.posX && ball.posY < block.posY + BLOCK_HEIGHT && ball.posY > block.posY;
  right = ball.posX >= block.posX && ball.posY < block.posY + BLOCK_HEIGHT && ball.posY > block.posY;
  down = ball.posX > block.posX && ball.posX < block.posX + BLOCK_WIDHT && ball.posY < block.posY + BLOCK_HEIGHT;
  up = ball.posX > block.posX && ball.posX < block.posX + BLOCK_WIDHT && ball.posY < block.posY;
  (i+1) to move the image
  */

  /* down */
  if (ball->posX + 15 >= block.posX && ball->posX <= block.posX + BLOCK_WIDHT && ball->posY <= block.posY) {
    ball->stepY = -ball->stepY;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(j+1);
  }

  /* left */
  else if (ball->posX + 15 == block.posX && ball->posY <= block.posY + BLOCK_HEIGHT && ball->posY >= block.posY) {
    ball->stepX = -ball->stepX;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(j+1);
  }

  /* right */
  else if (ball->posX == block.posX && ball->posY <= block.posY + BLOCK_HEIGHT && ball->posY >= block.posY) {
    ball->stepX = -ball->stepX;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(j+1);
  }

  /*
  else if (ball->posX >= block.posX && ball->posX <= block.posX + BLOCK_WIDHT && ball->posY <= block.posY) {
    ball->stepY = -ball->stepY;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(j+1);
  }*/

  /* critical collision */
  /*else if ((ball->posX - block.posX)*(ball->posX - block.posX) + (ball->posY - block.posY)*(ball->posY - block.posY) <= (block.posY + BLOCK_HEIGHT)*(block.posY + BLOCK_HEIGHT)) {
    ball->stepX = -ball->stepX;
    ball->stepY = -ball->stepY;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(j+1);
  }*/
  return block;
}


void moveOBJECT(OBJECT *p) {
    p->posX += p->stepX;
    p->posY += p->stepY;

    if ((p->posX + 15 > SCREEN_WIDTH) || (p->posX < 0) ) {
        p->stepX = -p->stepX;
        p->posX += p->stepX;
    }
    if ((p->posY + 15 > SCREEN_HEIGHT) || (p->posY < 0)) {
        p->stepY = -p->stepY;
        p->posY += p->stepY;
    }
}

OBJECT createOBJECT(int posX, int posY, int stepX, int stepY, SDL_Surface *image) {
    OBJECT p;

    p.posX = posX;
    p.posY = posY;
    p.stepX = stepX;
    p.stepY = stepY;
    p.image = image;
    return p;
}

int init() {
    /*Initialization flag*/
    int success = true;

    srand(time(NULL));

    /*Initialize SDL*/
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        /*Create window*/
        gWindow = SDL_CreateWindow("Breakout game. Have fun!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            /*Initialize JPG and PNG loading */
            int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else {
                /*Get window surface*/
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

int loadMedia() {
    /*Loading success flag*/
    int success = true;
    /*uint32_t colorKey;*/

    /*Load ball surface*/
    gBallSurface = loadSurface("./bola.png");

    /* load bar surface */
  /*gBarSurface = loadSurface( INSERT BAR'S IMAGE PATH HERE );*/

    /* load block surface */
    gBlockSurface = loadSurface("./big_brick.png");
    if(gBallSurface == NULL || gBlockSurface == NULL) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface( char *path ) {
  /*The final optimized image*/
  SDL_Surface* optimizedSurface = NULL;

  /*Load image at specified path*/
  SDL_Surface* loadedSurface = IMG_Load(path);
  if(loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
  }
  else {
    /*Convert surface to screen format*/
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0);
    if(optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
    }

    /*Get rid of old loaded surface*/
    SDL_FreeSurface(loadedSurface);
  }

  return optimizedSurface;
}

void closing() {
    /*Free ball image*/
    SDL_FreeSurface(gBallSurface);
    gBallSurface = NULL;

    /* Free bar image */
  /*  SDL_FreeSurface(gBarSurface);
    gBarSurface = NULL;
*/
    /* Free block surface */
    SDL_FreeSurface(gBlockSurface);
    gBlockSurface = NULL;

    /*Destroy window*/
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    /*Quit SDL subsystems*/
    IMG_Quit();
    SDL_Quit();
}
