#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "defs.h"

int gQuit = false;
int gPoints = 0;
int gLifes = 3;
/* The window we'll be rendering to */
SDL_Window *gWindow = NULL;
/* The surface contained by the window */
SDL_Surface *gScreenSurface = NULL;
/* The surface displaying the menu */
SDL_Surface *gMenuSurface = NULL;
/* Current displayed ball image */
SDL_Surface *gBallSurface = NULL;
/* blocks' surface */
SDL_Surface *gFirstBlockSurface = NULL;
SDL_Surface *gSecondBlockSurface = NULL;
SDL_Surface *gThirdBlockSurface = NULL;
/* bar's surface */
SDL_Surface *gBarSurface = NULL;
/*sounds */
Mix_Chunk *gCollisionBarSound = NULL;
Mix_Chunk *gCollisionBlockSound = NULL;
Mix_Chunk *gDestroyBlockSound = NULL;
