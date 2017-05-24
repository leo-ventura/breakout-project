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
#define BLOCK_HEIGHT 90

/*SDL_Surface* screen
SDL_Window* window;
SDL_Event event;*/

/*Funcao para abrir a tela em fullscreen
SDL_SetWindowFullscreen(SDL_Window* window, flags)*/



/* Constants */
const int true = 1;
const int false = 0;

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
SDL_Window* gWindow = NULL;

/* Characters image */
OBJECT bar;

/* The surface contained by the window */
SDL_Surface* gScreenSurface = NULL;

/* Current displayed PNG image */
SDL_Surface* gBallSurface = NULL;

/* Functions prototypes */

/*Starts up SDL and creates window*/
int init();

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
BLOCK collision(BLOCK block, OBJECT *ball, int i);


/* starts main function */



int main(int argc, char const *argv[]) {
  /* local variables */
  SDL_Rect srcRect, dstRect;
  int quit;
  int i;
  /* event handler */
  SDL_Event e;

  /* Start up SDL and create window */
  if (!init())  {
      printf("SDL could not be initialized\n");
  }

  if (!loadMedia()) {
    printf("Media could not be loaded\n");
  }
  /* MAIN MENU CODE HERE */

  /* create ball object */
  ball = createOBJECT(SCREEN_WIDTH/2, (3*SCREEN_HEIGHT/4)+1), 0, 0, gJPGSurface);
  /* create bar object */
  bar = createOBJECT(SCREEN_WIDTH/2, (3*SCREEN_HEIGHT/4), 0, 0, gJPGSurface);

  /* loop to create blocks */
  for (i = 0; i < )

  /* Starts game main loop */
  while(SDL_PollEvent(&e) != 0) {
    /* user request quit*/
    if (e.type == SDL_Quit) {
      quit = true;
    }
    else if (e.type == SDL_KEYDOWN) {
      switch(e.key.keysym.sym) {
        /* user taps left arrow */
        case SDLK_LEFT:
          bar.posX -= bar.stepX;
          break;
        /* user taps right arrow */
        case SDLK_RIGHT:
          bar.posX += bar.stepX;
          break;
      }

      /* Fill screen surface with white */
      SDL_FillRect(gScreenSurface, NULL,
                    SDL_MapRGB( gScreenSurface->format,
                    0x00, 0x00, 0x00));

    }
  }

  return 0;
}


void drawBlock(BLOCK b, SDL_Rect srcBlock) {
  SDL_Rect dstRect;
  dstRect.x = b.posX;
  dstRect.y = b.posY;
  SDL_BlitSurface(b.image, &srcBlock, gScreenSurface, &dstRect);
}

BLOCK createBLOCK(int posX, int posY, int resistance, SDL_Surface *image) {
  BLOCK b;
  b.posX = posX;
  b.posY = posY;
  b.resistance = resistance;
  b.image = image;
  return b;
}

BLOCK collision(BLOCK block, NPC *ball, int i) {
  /*left = ball.posX <= block.posX && ball.posY < block.posY + BLOCK_HEIGHT && ball.posY > block.posY;
  right = ball.posX >= block.posX && ball.posY < block.posY + BLOCK_HEIGHT && ball.posY > block.posY;
  down = ball.posX > block.posX && ball.posX < block.posX + BLOCK_WIDHT && ball.posY < block.posY + BLOCK_HEIGHT;
  up = ball.posX > block.posX && ball.posX < block.posX + BLOCK_WIDHT && ball.posY < block.posY;
  (i+1) to move the image
  */

  if (ball->posX > block.posX && ball->posX < block.posX + BLOCK_WIDHT && ball->posY < block.posY + BLOCK_HEIGHT) {
    ball->stepY = -ball->stepY;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(i+1);
  }
  else if (ball->posX == block.posX && ball->posY < block.posY + BLOCK_HEIGHT && ball->posY > block.posY) {
    ball->stepX = -ball->stepX;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(i+1);
  }
  else if (ball->posX == block.posX && ball->posY < block.posY + BLOCK_HEIGHT && ball->posY > block.posY) {
    ball->stepX = -ball->stepX;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(i+1);
  }
  else if (ball.posX > block.posX && ball.posX < block.posX + BLOCK_WIDHT && ball.posY < block.posY) {
    ball->stepY = -ball.stepY;
    block.resistance -= 1;
    block.posX = -BLOCK_WIDHT*(i+1);
    block.posY = -BLOCK_HEIGHT*(i+1);
  }
  return block;
}


void moveOBJECT(OBJECT *p) {
    p->posX += p->stepX;
    p->posY += p->stepY;

    if ( (p->posX + IMAGE_WIDTH > SCREEN_WIDTH) ||
         (p->posX < 0) ) {
        p->stepX = -p->stepX;
        p->posX += p->stepX;
    }
    if ( (p->posY + IMAGE_HEIGHT > SCREEN_HEIGHT) ||
         (p->posY < 0) ) {
        p->stepY = -p->stepY;
        p->posY += p->stepY;
    }
}

OBJECT createOBJECT( int posX, int posY, int stepX, int stepY,
               SDL_Surface *image) {
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
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            /*Initialize JPG and PNG loading */
            int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else {
                /*Get window surface*/
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }
    return sucess;
}

int loadMedia() {
    /*Loading success flag*/
    int success = true;
    /*uint32_t colorKey;*/

    /*Load ball surface*/
    gBallSurface = loadSurface(/*"INSERT BALL'S IMAGE PATH HERE"*/ );

    /* load block surface */
    gBlockSurface = loadSurface(/*INSERT BAR'S IMAGE PATH HERE */)
    if( gBallSurface == NULL ) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface( char *path ) {
  /*The final optimized image*/
  SDL_Surface* optimizedSurface = NULL;

  /*Load image at specified path*/
  SDL_Surface* loadedSurface = IMG_Load( path );
  if( loadedSurface == NULL ) {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
  }
  else {
    /*Convert surface to screen format*/
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if( optimizedSurface == NULL ) {
      printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
    }

    /*Get rid of old loaded surface*/
    SDL_FreeSurface( loadedSurface );
  }

  return optimizedSurface;
}

void closing() {
    /*Free loaded image*/
    SDL_FreeSurface( gJPGSurface );
    gJPGSurface = NULL;

    /*Destroy window*/
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    /*Quit SDL subsystems*/
    IMG_Quit();
    SDL_Quit();
}
