#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*Starts up SDL and creates window*/
int init();
int loadMedia();
void closing();
SDL_Surface* loadSurface(char*); /* Loads individual image */
OBJECT createOBJECT(double, double, double, double, SDL_Surface*);
void moveOBJECT(OBJECT*);
void moveBAR(OBJECT*, OBJECT*, int );
BLOCK createBLOCK(int, int, SDL_Surface*, int);
void drawBlock(BLOCK, SDL_Rect);
void collisionBlock(BLOCK*, OBJECT*, int*);
double distance(double, double, double, double);
void gameOver(OBJECT*, OBJECT*, int*); /* check wheter player loses one life */
void collisionBar(OBJECT, OBJECT*);
void keyPressed(OBJECT*, OBJECT*, SDL_Event, int*);
void stageOne();
void stageTwo();
void stageThree();

#endif
