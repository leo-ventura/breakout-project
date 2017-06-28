#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"

unsigned int next_time;
int gQuit = false;
int gPoints;
int gLifes;
int gSoundCondition = true;
int gMusicCondition = true;
int gVolume = 10;
int gBarColor = GREEN;
int gBallColor = BLUE;
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
SDL_Surface *gMusicButton = NULL;
SDL_Surface *gSoundButton = NULL;
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
