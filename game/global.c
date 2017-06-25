#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"

int gQuit = false;
int gPoints = 0;
int gLifes = 3;
int gSoundCondition = 1;
int gMusicCondition = 1;
int gVolume = 10;
int gBarColor = 2;
int gBallColor = 1;
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
SDL_Surface *gSelectedOption = NULL;

/*sounds */
Mix_Chunk *gCollisionBarSound = NULL;
Mix_Chunk *gCollisionBlockSound = NULL;
Mix_Chunk *gDestroyBlockSound = NULL;
Mix_Music *gStageOneMusic = NULL;
/*
Mix_Music *gStageTwoMusic = NULL;
Mix_Music *gStageThreeMusic = NULL;
*/
/* fonts */
TTF_Font *gFont = NULL;
SDL_Surface *gRankingText = NULL;
SDL_Surface *gSettingsText = NULL;
SDL_Surface *gMenuText = NULL;
SDL_Surface *gInGamePoints = NULL;
SDL_Surface *gInGameLife = NULL;
SDL_Surface *gInGameBlocks = NULL;
SDL_Surface *gInGameOptions = NULL;
