#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"

int gQuit = false;
int gPoints = 0;
int gLifes = 3;
/* The window we'll be rendering to */
SDL_Window *gWindow = NULL;
/* The surface contained by the window */
SDL_Surface *gScreenSurface = NULL;
/* The surface we'll be displaying the menu */
SDL_Surface *gMenuSurface = NULL;
/* Current displayed ball image */
SDL_Surface *gBallSurface = NULL;
/* blocks' surface */
SDL_Surface *gBlockSurface = NULL;
/* bar's surface */
SDL_Surface *gBarSurface = NULL;
/* npcBar's surface */
SDL_Surface *gNpcBarSurface = NULL;
/*sounds */
Mix_Chunk *gCollisionBarSound = NULL;
Mix_Chunk *gCollisionBlockSound = NULL;
Mix_Chunk *gDestroyBlockSound = NULL;
/* fonts */
TTF_Font *gFont = NULL;
SDL_Surface *gRankingText = NULL;
SDL_Surface *gMenuText = NULL;
SDL_Surface *gInGamePoints = NULL;
SDL_Surface *gInGameLife = NULL;
SDL_Surface *gInGameBlocks = NULL;
SDL_Surface *gInGameOptions = NULL;
SDL_Surface *gStartSelected = NULL;
SDL_Surface *gRankingSelected = NULL;
SDL_Surface *gSettingsSelected = NULL;
SDL_Surface *gHelpSelected = NULL;
SDL_Surface *gExitSelected = NULL;
