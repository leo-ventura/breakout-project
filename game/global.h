#ifndef GLOBAL_H
#define GLOBAL_H

extern const unsigned int TICK_INTERVAL;
extern unsigned int next_time;
extern int gQuit;
extern int gPoints;
extern int gLifes;
extern int gBarColor;
extern int gBallColor;
extern int gSoundCondition;
extern int gMusicCondition;
extern int gVolume;
extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *gMenuSurface;
extern SDL_Surface *gBallSurface;
extern SDL_Surface *gBlockSurface;
extern SDL_Surface *gBarSurface;
extern SDL_Surface *gNpcBarSurface;
extern SDL_Surface *gSelectedOption;
extern SDL_Surface *gMusicButton;
extern SDL_Surface *gSoundButton;
extern Mix_Chunk *gCollisionBarSound;
extern Mix_Chunk *gCollisionBlockSound;
extern Mix_Chunk *gDestroyBlockSound;
extern Mix_Music *gStageOneMusic;
extern TTF_Font *gFont;
extern SDL_Surface *gRankingText;
extern SDL_Surface *gSettingsText;
extern SDL_Surface *gMenuText;
extern SDL_Surface *gInGamePoints;
extern SDL_Surface *gInGameLife;
extern SDL_Surface *gInGameBlocks;
extern SDL_Surface *gInGameOptions;
extern SDL_Surface *gStartSelected;
extern SDL_Surface *gRankingSelected;
extern SDL_Surface *gSettingsSelected;
extern SDL_Surface *gHelpSelected;
extern SDL_Surface *gExitSelected;

#endif
