#ifndef GLOBAL_H
#define GLOBAL_H

extern int gQuit;
extern int gPoints;
extern int gLifes;
extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *gMenuSurface;
extern SDL_Surface *gBallSurface;
extern SDL_Surface *gFirstBlockSurface;
extern SDL_Surface *gSecondBlockSurface;
extern SDL_Surface *gThirdBlockSurface;
extern SDL_Surface *gBarSurface;
extern Mix_Chunk *gCollisionBarSound;
extern Mix_Chunk *gCollisionBlockSound;
extern Mix_Chunk *gDestroyBlockSound;

#endif
