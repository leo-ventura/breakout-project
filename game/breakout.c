/* This is a version of the game Breakout developed by students from Federal
* University of Rio de Janeiro.
* Developers: Breno Coll, Breno Tostes e Leonardo Ventura
* Professor: Adriano Cruz
*/

/* Using SDL, SDL_image, stdio, strings and time*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*SDL_Surface* screen
SDL_Window* window;
SDL_Event event;*/

/*Funcao para abrir a tela em fullscreen
SDL_SetWindowFullscreen(SDL_Window* window, flags)*/



/* Constants */
const int true = 1;
const int false = 0;

/* Defining structures */
typedef struct _OBJECT {
  int posX;
  int posY;
  int stepX;
  int stepY;
  SDL_Surface* image;
  int imgW;
  int imgH;
} OBJECT;

/* The window we'll be rendering to */
SDL_Window* gWindow = NULL;

/* Characters image */
OBJECT barra;

/* The surface contained by the window */
SDL_Surface* gScreenSurface = NULL;

/* Current displayed PNG image */
SDL_Surface* gJPGSurface = NULL;

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

int main(int argc, char const *argv[]) {
  return 0;
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
        gWindow = SDL_CreateWindow("Breakout game. Have fun!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

    /*Load PNG surface*/
    gJPGSurface = loadSurface(/*"INSERT CHARACTER IMAGE PATH HERE"*/ );
    if( gJPGSurface == NULL ) {
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
