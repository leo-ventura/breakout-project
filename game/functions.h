#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*Starts up SDL and creates window*/
int init();
int loadMedia();
void closing();
SDL_Surface* loadSurface(char*); /* Loads individual image */
OBJECT createOBJECT(double, double, double, double, SDL_Surface*);
void moveOBJECT(OBJECT*);
void moveNPCBAR(OBJECT*);
void moveBAR(OBJECT*, OBJECT*, int );
BLOCK createBLOCK(int, int, int, int, SDL_Surface*);
void drawBlock(BLOCK);
void collisionBlock(BLOCK*, OBJECT*, int*);
void collisionNpcBar(OBJECT, OBJECT*);
double distance(double, double, double, double);
void loseLife(OBJECT*, OBJECT*, int*); /* check wheter player loses one life */
void collisionBar(OBJECT, OBJECT*);
void keyPressed(OBJECT*, OBJECT*, SDL_Event, int*, int);
void pause(OBJECT*, OBJECT*, OBJECT*, SDL_Event, int*);
void quitPressed(SDL_Event);
void turnSound(SDL_Event);
void turnMusic(SDL_Event, int);
void menu();
void ranking();
void settings();
void help();
int stageOne();
int stageTwo();
int stageThree();
int loadTextMedia();
int loadInGameMenu();
int loadRenderedText(char *, SDL_Color);
void makeRank();
void getPlayerName(char *jogador);

#endif
