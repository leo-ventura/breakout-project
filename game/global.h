#ifndef GLOBAL_H
#define GLOBAL_H

extern int gQuit;
extern int gPoints;
extern int gLifes;
extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *gMenuSurface;
extern SDL_Surface *gBallSurface;
extern SDL_Surface *gBlockSurface;
extern SDL_Surface *gBarSurface;
extern SDL_Surface *gNpcBarSurface;
extern Mix_Chunk *gCollisionBarSound;
extern Mix_Chunk *gCollisionBlockSound;
extern Mix_Chunk *gDestroyBlockSound;
extern TTF_Font *gFont;
extern SDL_Surface *gRankingText;
extern SDL_Surface *gMenuText;
extern SDL_Surface *gInGameLife;
extern SDL_Surface *gInGameBlocks;
extern SDL_Surface *gInGameOptions;

#endif
