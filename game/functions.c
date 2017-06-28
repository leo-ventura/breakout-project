#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "defs.h"

unsigned time_left(void) {
    unsigned now = SDL_GetTicks();
    return (next_time <= now) ? 0 : next_time - now;
}

void drawBlock(BLOCK b) {
  SDL_Rect srcBlock;
  SDL_Rect dstBlock;
  switch (b.resistance) {
    case 1:
      switch (b.color) {
        case RED:
          srcBlock.x = 0;
          srcBlock.y = 0;
          break;
        case GREEN:
          srcBlock.x = BLOCK_WIDTH;
          srcBlock.y = 0;
          break;
        case YELLOW:
          srcBlock.x = 0;
          srcBlock.y = BLOCK_HEIGHT;
          break;
        case BLUE:
          srcBlock.x = BLOCK_WIDTH;
          srcBlock.y = BLOCK_HEIGHT;
          break;
        case PURPLE:
          srcBlock.x = 0;
          srcBlock.y = BLOCK_HEIGHT * 2;
          break;
      }
      break;
    case 2:
      srcBlock.x = BLOCK_WIDTH;
      srcBlock.y = BLOCK_HEIGHT * 2;
      break;
  }
  srcBlock.w = BLOCK_WIDTH;
  srcBlock.h = BLOCK_HEIGHT;
  dstBlock.x = b.posX;
  dstBlock.y = b.posY;
  SDL_BlitSurface(b.image, &srcBlock, gScreenSurface, &dstBlock);
}

BLOCK createBLOCK(int posX, int posY, SDL_Surface *image, int resistance, int color) {
  BLOCK b;
  b.posX = posX;
  b.posY = posY;
  b.resistance = resistance;
  b.image = image;
  b.color = color;
  return b;
}

double distance(double x1, double y1, double x2, double y2) {
  double dist = sqrt ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
  return dist;
}

void collisionBlock(BLOCK *block, OBJECT *ball, int *quantBlocks) {
  /*left = ball.posX <= block.posX && ball.posY < block.posY + BLOCK_HEIGHT && ball.posY > block.posY;
  right = ball.posX >= block.posX && ball.posY < block.posY + BLOCK_HEIGHT && ball.posY > block.posY;
  down = ball.posX > block.posX && ball.posX < block.posX + BLOCK_WIDTH && ball.posY < block.posY + BLOCK_HEIGHT;
  up = ball.posX > block.posX && ball.posX < block.posX + BLOCK_WIDTH && ball.posY < block.posY;
  */
  if (block->resistance > 0) {
    /* up and down */
    if (((ball->posY == block->posY + BLOCK_HEIGHT) ||
        (ball->posY + BALL_HEIGHT == block->posY)) &&
        (ball->posX + BALL_WIDTH/2 > block->posX) &&
        (ball->posX + BALL_WIDTH/2 < block->posX + BLOCK_WIDTH)){
          ball->stepY *= -1;
          ball->posY += ball->stepY;
          block->resistance--;
          if (block->resistance == 0){
            (*quantBlocks)--;
            gPoints += 100;
            if (gSoundCondition) Mix_PlayChannel(-1, gDestroyBlockSound, 0);
          }
          else {
            if (gSoundCondition) if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBlockSound, 0);
          }
    }
    /* right and left */
    else if (((ball->posX <= block->posX + BLOCK_WIDTH && ball->posX > block->posX) ||
         (ball->posX + BALL_WIDTH >= block->posX && ball->posX + BALL_WIDTH < block->posX + BLOCK_WIDTH )) &&
         (ball->posY + BALL_HEIGHT/2 > block->posY) &&
         (ball->posY + BALL_HEIGHT/2 < block->posY + BLOCK_HEIGHT)){
            ball->stepX *= -1;
            ball->posX += ball->stepX;
            block->resistance--;
            if (block->resistance == 0){
              (*quantBlocks)--;
              gPoints += 100;
              if (gSoundCondition) if (gSoundCondition) Mix_PlayChannel(-1, gDestroyBlockSound, 0);
            }
            else {
              if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBlockSound, 0);
            }
    }
    /* upper left */
    else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, block->posX, block->posY) < BALL_WIDTH/2){
      if (ball->stepX > 0) {
        ball->stepX *= -1;
      }
      if (ball->stepY > 0) {
        ball->stepY *= -1;
      }
      ball->posX += ball->stepX;
      ball->posY += ball->stepY;
      block->resistance --;
      if (block->resistance == 0){
        (*quantBlocks)--;
        gPoints += 100;
        if (gSoundCondition) Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBlockSound, 0);
      }
    }

    /* lower left */
    else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, block->posX, block->posY + BLOCK_HEIGHT) < BALL_WIDTH/2){
      if (ball->stepX > 0) {
        ball->stepX *= -1;
      }
      if (ball->stepY < 0) {
        ball->stepY *= -1;
      }
      ball->posX += ball->stepX;
      ball->posY += ball->stepY;
      block->resistance --;
      if (block->resistance == 0){
        (*quantBlocks)--;
        gPoints += 100;
        if (gSoundCondition) Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBlockSound, 0);
      }
    }

    /* lower right */
    else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, block->posX + BLOCK_WIDTH, block->posY + BLOCK_HEIGHT) < BALL_WIDTH/2){
      if (ball->stepX < 0) {
        ball->stepX *= -1;
      }
      if (ball->stepY < 0) {
        ball->stepY *= -1;
      }
      ball->posX += ball->stepX;
      ball->posY += ball->stepY;
      block->resistance --;
      if (block->resistance == 0){
        (*quantBlocks)--;
        gPoints += 100;
        if (gSoundCondition) Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBlockSound, 0);
      }
    }

    /* upper right */
    else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, block->posX + BLOCK_WIDTH, block->posY) < BALL_WIDTH/2){
      if (ball->stepX < 0) {
        ball->stepX *= -1;
      }
      if (ball->stepY > 0) {
        ball->stepY *= -1;
      }
      ball->posX += ball->stepX;
      ball->posY += ball->stepY;
      block->resistance --;
      if (block->resistance == 0){
        (*quantBlocks)--;
        gPoints += 100;
        if (gSoundCondition) Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBlockSound, 0);
      }
    }
  }
}

void collisionNpcBar(OBJECT bar, OBJECT *ball) {
  /* up and down */
  if (((ball->posY == bar.posY + BAR_HEIGHT) ||
      (ball->posY + BALL_HEIGHT == bar.posY)) &&
      (ball->posX + BALL_WIDTH/2 >= bar.posX) &&
      (ball->posX + BALL_WIDTH/2 <= bar.posX + BAR_WIDTH)){
        ball->stepY *= -1;
        ball->posY += ball->stepY;
  }
  /* right */
  else if ((ball->posX <= bar.posX + BAR_WIDTH && ball->posX > bar.posX && ball->stepX < bar.stepX) &&
       (ball->posY + BALL_HEIGHT/2 >= bar.posY) &&
       (ball->posY + BALL_HEIGHT/2 <= bar.posY + BAR_HEIGHT)){
          ball->stepX = abs(ball->stepX)>NPCBAR_SPEED? ball->stepX*-1 : NPCBAR_SPEED + 0.1;
          ball->posX += ball->stepX;
  }

  /* left */
  else if ((ball->posX + BALL_WIDTH >= bar.posX && ball->posX + BALL_WIDTH < bar.posX + BAR_WIDTH && ball->stepX > bar.stepX ) &&
       (ball->posY + BALL_HEIGHT/2 >= bar.posY) &&
       (ball->posY + BALL_HEIGHT/2 <= bar.posY + BAR_HEIGHT)){
          ball->stepX = abs(ball->stepX)>NPCBAR_SPEED? ball->stepX*-1 : (NPCBAR_SPEED + 0.1)*-1;
          ball->posX += ball->stepX;
  }
  /* upper left */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX, bar.posY) < BALL_WIDTH/2){
    if (ball->stepX > bar.stepX) {
      ball->stepX = abs(ball->stepX)>NPCBAR_SPEED? ball->stepX*-1 : (NPCBAR_SPEED + 0.1)*-1;
    }
    if (ball->stepY > 0) {
      ball->stepY *= -1;
    }
    ball->posX += ball->stepX;
    ball->posY += ball->stepY;
  }

  /* lower left */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX, bar.posY + BAR_HEIGHT) < BALL_WIDTH/2){
    if (ball->stepX > bar.stepX) {
      ball->stepX = abs(ball->stepX)>NPCBAR_SPEED? ball->stepX*-1 : (NPCBAR_SPEED + 0.1)*-1;
    }
    if (ball->stepY < 0) {
      ball->stepY *= -1;
    }
    ball->posX += ball->stepX;
    ball->posY += ball->stepY;
  }

  /* lower right */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX + BAR_WIDTH, bar.posY + BAR_HEIGHT) < BALL_WIDTH/2){
    if (ball->stepX < bar.stepX) {
      ball->stepX = abs(ball->stepX)>NPCBAR_SPEED? ball->stepX*-1 : NPCBAR_SPEED + 0.1;
    }
    if (ball->stepY < 0) {
      ball->stepY *= -1;
    }
    ball->posX += ball->stepX;
    ball->posY += ball->stepY;
  }

  /* upper right */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX + BAR_WIDTH, bar.posY) < BALL_WIDTH/2){
    if (ball->stepX < bar.stepX) {
      ball->stepX = abs(ball->stepX)>NPCBAR_SPEED? ball->stepX*-1 : NPCBAR_SPEED + 0.1;
    }
    if (ball->stepY > 0) {
      ball->stepY *= -1;
    }
    ball->posX += ball->stepX;
    ball->posY += ball->stepY;
  }
}

void collisionBar(OBJECT bar, OBJECT *ball){
  if (ball->stepY != 0){
    if (((ball->posY + BALL_HEIGHT == bar.posY) &&
        (ball->posX + BALL_WIDTH/2 > bar.posX) &&
        (ball->posX + BALL_WIDTH/2 < bar.posX + BAR_WIDTH)) ||
        (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX, bar.posY) < BALL_WIDTH/2) ||
        (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX + BAR_WIDTH, bar.posY) < BALL_WIDTH/2)
        ) {
          ball->stepY *= -1;
          ball->stepX = ((ball->posX + BALL_WIDTH/2) - (bar.posX + BAR_WIDTH/2))/40;
          ball->posY += ball->stepY;
          ball->posX += ball->stepX;
          if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBarSound, 0);
    }
    else if (((ball->posX <= bar.posX + BAR_WIDTH && ball->posX > bar.posX) ||
         (ball->posX + BALL_WIDTH >= bar.posX && ball->posX + BALL_WIDTH < bar.posX + BAR_WIDTH )) &&
         (ball->posY + BALL_HEIGHT/2 > bar.posY) &&
         (ball->posY + BALL_HEIGHT/2 < bar.posY + BAR_HEIGHT)) {
           ball->stepX = ((ball->posX + BALL_WIDTH/2) - (bar.posX + BAR_WIDTH/2))/40;
           ball->posY += ball->stepY;
           ball->posX += ball->stepX;
           if (gSoundCondition) Mix_PlayChannel(-1, gCollisionBarSound, 0);
    }
  }
}

void moveOBJECT(OBJECT *p) {
    p->posX += p->stepX;
    p->posY += p->stepY;

    if ((p->posX + BALL_WIDTH > SCREEN_WIDTH) || (p->posX < 0) ) {
        p->stepX = -p->stepX;
        p->posX += p->stepX;
    }
    if (p->posY < 0) {
        p->stepY = -p->stepY;
        p->posY += p->stepY;
    }
}

void moveNPCBAR(OBJECT *p) {
    p->posX += p->stepX;
    p->posY += p->stepY;

    if ((p->posX + BAR_WIDTH > SCREEN_WIDTH) || (p->posX < 0) ) {
        p->stepX = -p->stepX;
        p->posX += p->stepX;
    }
    if (p->posY < 0) {
        p->stepY = -p->stepY;
        p->posY += p->stepY;
    }
}

void loseLife(OBJECT *ball, OBJECT *bar, int *gameStarted){
  if (ball->posY > SCREEN_HEIGHT){
    gLifes--;
    *gameStarted = false;
    ball->posX = SCREEN_WIDTH/2 - BALL_WIDTH/2;
    ball->posY = SCREEN_HEIGHT - 100 - BALL_HEIGHT;
    ball->stepX = 0;
    ball->stepY = 0;
    bar->posX = SCREEN_WIDTH/2 - BAR_WIDTH/2;
    bar->posY = SCREEN_HEIGHT - 100;
    bar->stepX = 0;
    bar->stepY = 0;
  }
}

void moveBAR(OBJECT *p, OBJECT *ball, int gameStarted) {
    if ((p->posX + BAR_WIDTH >= SCREEN_WIDTH) && (p->stepX > 0) ) {
        p->stepX = 0;
        p->posX += p->stepX;
        if (!gameStarted) ball->stepX = 0;
    }
    if ((p->posX < 0) && (p->stepX < 0) ) {
        p->stepX = 0;
        p->posX += p->stepX;
        if (!gameStarted) ball->stepX = 0;
    }
    p->posX += p->stepX;
    p->posY += p->stepY;
}

OBJECT createOBJECT(double posX, double posY, double stepX, double stepY, SDL_Surface *image) {
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
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_AllocateChannels(16);

    if (TTF_Init() == -1) {
      printf("TTF unable to initialize! Error: %s\n", TTF_GetError());
      success = false;
    }

    /*Initialize SDL*/
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        /*Create window*/
        gWindow = SDL_CreateWindow("Breakout game. Have fun!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            /*Initialize JPG and PNG loading */
            int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else {
                /*Get window surface*/
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

SDL_Surface* loadSurface( char *path ) {
  /*The final optimized image*/
  SDL_Surface* optimizedSurface = NULL;

  /*Load image at specified path*/
  SDL_Surface* loadedSurface = IMG_Load(path);
  if(loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
  }
  else {
    /*Convert surface to screen format*/
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0);
    if(optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
    }

    /*Get rid of old loaded surface*/
    SDL_FreeSurface(loadedSurface);
  }

  return optimizedSurface;
}

SDL_Surface *loadRenderedText(char *text, SDL_Color textcolor) {
  SDL_Surface *optimizedTextSurface;

  SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text, textcolor);
  if (!textSurface) {
    printf("Unable to render text. Error: %s\n", TTF_GetError());
    return false;
  }

  optimizedTextSurface = SDL_ConvertSurface(textSurface, gScreenSurface->format, 0);
  if (!optimizedTextSurface) {
    printf("Unable to create texture. Error: %s\n", TTF_GetError());
    return false;
  }
  SDL_FreeSurface(textSurface);

  return optimizedTextSurface;
}

SDL_Surface *loadGetNameRenderedText(TTF_Font *font, char *text, SDL_Color textcolor) {
  SDL_Surface *optimizedTextSurface;

  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textcolor);
  if (!textSurface) {
    printf("Unable to render text. Error: %s\n", TTF_GetError());
    return false;
  }

  optimizedTextSurface = SDL_ConvertSurface(textSurface, gScreenSurface->format, 0);
  if (!optimizedTextSurface) {
    printf("Unable to create texture. Error: %s\n", TTF_GetError());
    return false;
  }
  SDL_FreeSurface(textSurface);

  return optimizedTextSurface;
}

int loadInGameMenu() {
  int success = true;
  gFont = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 20);
  if (!gFont) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
    success = false;
  }
  return success;
}

int loadMedia() {
    /*Loading success flag*/
    int success = true;
    /* Load menu surface */
    gMenuSurface = loadSurface("../image_library/menu_screen.png");

    /*Load ball surface*/
    gBallSurface = loadSurface("../image_library/bola.png");
    SDL_SetColorKey( gBallSurface, SDL_TRUE, SDL_MapRGB( gBallSurface->format, 0xFF, 0xFF, 0xFF ) );

    /* load bar surface */
    gBarSurface = loadSurface("../image_library/bar.png");

    /* load block surface */
    gBlockSurface = loadSurface("../image_library/block.png");

    /* non-player bar */
    gNpcBarSurface = loadSurface("../image_library/NPCbar.png");

    gSelectedOption = loadSurface("../image_library/select.png");

    gMusicButton = loadSurface("../image_library/musicOnOff.png");

    gSoundButton = loadSurface("../image_library/soundOnOff.png");

    if(!gBallSurface || !gBlockSurface || !gBarSurface || !gNpcBarSurface || !gMenuSurface || !gSelectedOption
        || !gMusicButton || !gSoundButton) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    /*load sounds */
    gCollisionBarSound = Mix_LoadWAV("../sound_library/collisionBar.wav");
    gCollisionBlockSound = Mix_LoadWAV("../sound_library/collisionBlock.wav");
    gDestroyBlockSound = Mix_LoadWAV("../sound_library/destroyBlock.wav");
    gStageOneMusic = Mix_LoadMUS("../sound_library/music.mod");
    /*
    gStageTwoMusic = Mix_LoadMUS("../sound_library/stageTwoMusic.mp3");
    gStageThreeMusic = Mix_LoadMUS("../sound_library/stageThreeMusic.mp3");
    */

    if (!gCollisionBlockSound || !gCollisionBarSound || !gDestroyBlockSound || !gStageOneMusic /*|| !gStageTwoMusic|| !gStageTwoMusic*/) {
      printf("Failed to load sounds! SDL Error: %s\n", SDL_GetError());
      success = false;
    }

    return success;
}

void closing() {
    /*Free ball image*/
    SDL_FreeSurface(gBallSurface);
    gBallSurface = NULL;

    SDL_FreeSurface(gMenuSurface);
    gMenuSurface = NULL;

    /* Close font */
    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_FreeSurface(gSelectedOption);
    gSelectedOption = NULL;

    /* Free fonts' surface */
    SDL_FreeSurface(gRankingText);
    SDL_FreeSurface(gMenuText);
    gRankingText = NULL;
    gMenuText = NULL;

    /* Free bar image */
    SDL_FreeSurface(gBarSurface);
    gBarSurface = NULL;

    /* Free block surface */
    SDL_FreeSurface(gBlockSurface);
    gBlockSurface = NULL;

    /* Free npcBar surface */
    SDL_FreeSurface(gNpcBarSurface);
    gNpcBarSurface = NULL;

    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;

    /*Destroy window*/
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    /*Free sounds */
    Mix_FreeChunk(gCollisionBarSound);
    Mix_FreeChunk(gCollisionBlockSound);
    Mix_FreeChunk(gDestroyBlockSound);
    Mix_FreeMusic(gStageOneMusic);
    /*
    Mix_FreeMusic(gStageOneMusic);
    Mix_FreeMusic(gStageOneMusic);
    */
    /*Quit SDL subsystems*/
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void turnSound(SDL_Event e) {
  switch (e.type) {
    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_s) {
        gSoundCondition = !gSoundCondition;
      }
  }
}

void turnMusic(SDL_Event e, int stage) {
  switch (e.type) {
    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_m) {
        if (!gMusicCondition){
          if (Mix_PausedMusic()) {
            Mix_ResumeMusic();
          }
          else {
            switch (stage) {
              case 1:
                Mix_PlayMusic(gStageOneMusic, -1);
                break;
              /*
              case 2:
                Mix_PlayMusic(gStageTwoMusic, -1);
                break;
              case 3:
                Mix_PlayMusic(gStageThreeMusic, -1);
                break;
              */
            }
          }
        }
        else {
          Mix_PauseMusic();
        }
        gMusicCondition = !gMusicCondition;
      }
  }
}

void quitPressed(SDL_Event e) {
  switch(e.type) {
      case SDL_QUIT:
        gQuit = true;
        break;
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE) {
            gQuit = true;
        }
        break;
  }
}

void pause(OBJECT* ball, OBJECT* bar, OBJECT* bar2, SDL_Event e, int* pausedGame) {
  static OBJECT oldBall;
  static OBJECT oldBar;
  static OBJECT oldBar2;
  /*SDL_Surface *pauseSurface;
  TTF_Font *font;
  SDL_Rect dstPause;
  SDL_Color textcolor = {0, 0, 0};

  font = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 55);
  if (!font) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }

  pauseSurface = loadGetNameRenderedText(font, "PAUSED", textcolor);

  dstPause.x = SCREEN_WIDTH/2 - 50;
  dstPause.y = WINDOW_HEIGHT/2 - 80;

  if (SDL_BlitSurface(pauseSurface, NULL, gScreenSurface, &dstPause) < 0) {
    printf("Error while blitting ranking surface!\n");
    gQuit = true;
  }*/
  switch (e.type) {
    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_p){
        if (!*pausedGame) {
          oldBall = *ball;
          oldBar = *bar;
          oldBar2 = *bar2;
          ball->stepX = 0;
          ball->stepY = 0;
          bar->stepX = 0;
          bar2->stepX = 0;
        }
        else {
          *bar = oldBar;
          *ball = oldBall;
          *bar2 = oldBar2;
        }
        *pausedGame = !*pausedGame;
      }
  }
}

void keyPressed(OBJECT *ball, OBJECT *bar, SDL_Event e, int *gameStarted, int pausedGame) {
  switch(e.type) {
      case SDL_KEYDOWN:
        if (!pausedGame){
          if(!*gameStarted) {
            if (e.key.keysym.sym == SDLK_LEFT) {
              ball->stepX = -1;
              bar->stepX = -1;
            }
            else if (e.key.keysym.sym == SDLK_RIGHT) {
              ball->stepX = 1;
              bar->stepX = 1;
            }
            else if (e.key.keysym.sym == SDLK_SPACE) {
              ball->stepX = 1;
              ball->stepY = -1;
              *gameStarted = true;
            }
          }
          else if (e.key.keysym.sym == SDLK_LEFT) {
            bar->stepX = -1;
          }
          else if (e.key.keysym.sym == SDLK_RIGHT) {
            bar->stepX = 1;
          }
        }
        break;
      case SDL_KEYUP:
        if (!*gameStarted){
          if (e.key.keysym.sym == SDLK_LEFT || SDLK_RIGHT){
            ball->stepX = 0;
            bar->stepX = 0;
          }
        }
        else {
          if (e.key.keysym.sym == SDLK_LEFT || SDLK_RIGHT){
            bar->stepX = 0;
          }
        }
        break;
  }
}

void settings() {
  SDL_Rect dstSettings;
  SDL_Event e;
  int returning = false;
  int cursor = 0;
  SDL_Color textcolor = {255, 255, 255};
  SDL_Surface *volumeSurface;
  SDL_Surface *musicSurface;
  SDL_Surface *soundSurface;
  SDL_Surface *ballColorSurface;
  SDL_Surface *barColorSurface;
  SDL_Surface *backSurface;
  SDL_Rect dstVolume;
  SDL_Rect dstMusic;
  SDL_Rect dstSound;
  SDL_Rect dstBallColor;
  SDL_Rect dstBarColor;
  SDL_Rect dstBack;
  SDL_Rect dstSelectedOption;
  TTF_Font *sfont = NULL;
  char volume[20];
  char music[20];
  char sound[20];
  char strBallColor[40];
  char strBarColor[40];
  char strVolume[5];

  sfont = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 35);
  if (!sfont) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }

  dstSettings.x = WINDOW_WIDTH/2 - 100;
  dstSettings.y = 50;

  dstVolume.x = WINDOW_WIDTH/2 - 250;
  dstVolume.y = 150;

  dstMusic.x = WINDOW_WIDTH/2 - 250;
  dstMusic.y = 200;

  dstSound.x = WINDOW_WIDTH/2 - 250;
  dstSound.y = 250;

  dstBallColor.x = WINDOW_WIDTH/2 - 250;
  dstBallColor.y = 300;

  dstBarColor.x = WINDOW_WIDTH/2 - 250;
  dstBarColor.y = 350;

  dstBack.x = WINDOW_WIDTH/2 - 250;
  dstBack.y = 400;

  while(!gQuit && !returning) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
          case SDL_QUIT:
            gQuit = true;
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                gQuit = true;
            }
            if (e.key.keysym.sym == SDLK_UP) {
                cursor = (cursor+5)%6;
            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                cursor = (cursor+1)%6;
            }
            else if (e.key.keysym.sym == SDLK_RETURN) {
              switch(cursor) {
                case 1:
                  gMusicCondition = !gMusicCondition;
                  break;
                case 2:
                  gSoundCondition = !gSoundCondition;
                  break;
                case 5:
                  returning = true;
                  break;
              }
            }
            else if (e.key.keysym.sym == SDLK_RIGHT) {
              switch(cursor) {
                case 0:
                  gVolume = (gVolume+1)%11;
                  break;
                case 1:
                  gMusicCondition = !gMusicCondition;
                  break;
                case 2:
                  gSoundCondition = !gSoundCondition;
                  break;
                case 3:
                  gBallColor = (gBallColor+1)%4;
                  break;
                case 4:
                  gBarColor = (gBarColor+1)%4;
                  break;
              }
            }
            else if (e.key.keysym.sym == SDLK_LEFT) {
              switch(cursor) {
                case 0:
                  gVolume = (gVolume+10)%11;
                  break;
                case 1:
                  gMusicCondition = !gMusicCondition;
                  break;
                case 2:
                  gSoundCondition = !gSoundCondition;
                  break;
                case 3:
                  gBallColor = (gBallColor+3)%4;
                  break;
                case 4:
                  gBarColor = (gBarColor+3)%4;
                  break;
              }
            }


      }

      switch (cursor) {
        case 0:
          dstSelectedOption.y = 150;
          break;
        case 1:
          dstSelectedOption.y = 200;
          break;
        case 2:
          dstSelectedOption.y = 250;
          break;
        case 3:
          dstSelectedOption.y = 300;
          break;
        case 4:
          dstSelectedOption.y = 350;
          break;
        case 5:
          dstSelectedOption.y = 400;
          break;
      }
      dstSelectedOption.x = WINDOW_WIDTH/2 - 270 - SELECT_WIDTH;

      strcpy(music, "Music: ");
      strcat(music, gMusicCondition? "On" : "Off");
      strcpy(sound, "Sound: ");
      strcat(sound, gSoundCondition? "On" : "Off");
      strcpy(strBallColor, "Ball Color: ");
      strcat(strBallColor, gBallColor==0? "Red" : gBallColor==1? "Blue" : gBallColor==2? "Green" : "Yellow");
      strcpy(strBarColor, "Bar Color: ");
      strcat(strBarColor, gBarColor==0? "Red" : gBarColor==1? "Blue" : gBarColor==2? "Green" : "Yellow");
      strcpy(volume, "Volume: ");
      sprintf(strVolume, "%d", gVolume);
      strcat(volume, strVolume);

      gSettingsText = loadGetNameRenderedText(sfont, "Settings", textcolor);
      volumeSurface = loadGetNameRenderedText(sfont, volume, textcolor);
      musicSurface = loadGetNameRenderedText(sfont, music, textcolor);
      soundSurface = loadGetNameRenderedText(sfont, sound, textcolor);
      ballColorSurface = loadGetNameRenderedText(sfont, strBallColor, textcolor);
      barColorSurface = loadGetNameRenderedText(sfont, strBarColor, textcolor);
      backSurface = loadGetNameRenderedText(sfont, "Back", textcolor);

      if (!gSettingsText || !volumeSurface || !musicSurface || !soundSurface || !ballColorSurface || !barColorSurface || !backSurface) {
        printf("Failed to render text! Error: %s\n", TTF_GetError());
        gQuit = true;
      }

      SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
      if (SDL_BlitSurface(gSettingsText, NULL, gScreenSurface, &dstSettings) < 0 ||
          SDL_BlitSurface(volumeSurface, NULL, gScreenSurface, &dstVolume) < 0 ||
          SDL_BlitSurface(musicSurface, NULL, gScreenSurface, &dstMusic) < 0 ||
          SDL_BlitSurface(soundSurface, NULL, gScreenSurface, &dstSound) < 0 ||
          SDL_BlitSurface(ballColorSurface, NULL, gScreenSurface, &dstBallColor) < 0 ||
          SDL_BlitSurface(barColorSurface, NULL, gScreenSurface, &dstBarColor) < 0 ||
          SDL_BlitSurface(backSurface, NULL, gScreenSurface, &dstBack) < 0 ||
          SDL_BlitSurface(gSelectedOption, NULL, gScreenSurface, &dstSelectedOption) < 0) {
        printf("Error while blitting ranking surface!\n");
      }
      SDL_UpdateWindowSurface(gWindow);
    }
  }
  SDL_FreeSurface(volumeSurface);
  SDL_FreeSurface(musicSurface);
  SDL_FreeSurface(soundSurface);
  SDL_FreeSurface(ballColorSurface);
  SDL_FreeSurface(barColorSurface);
  SDL_FreeSurface(backSurface);
  Mix_VolumeChunk(gCollisionBarSound, VOLUME);
  Mix_VolumeChunk(gCollisionBlockSound, VOLUME);
  Mix_VolumeChunk(gDestroyBlockSound, VOLUME);
}

void help() {
  SDL_Surface *helpSurface1;
  SDL_Surface *helpSurface12;
  SDL_Surface *helpSurface2;
  SDL_Surface *helpSurface22;
  SDL_Surface *helpSurface3;
  SDL_Surface *helpSurface4;
  SDL_Surface *helpSurface5;
  SDL_Surface *helpSurface6;
  SDL_Surface *helpSurface7;
  SDL_Surface *backSurface;
  SDL_Color textcolor = {255, 255, 255};
  SDL_Event e;
  SDL_Rect dstBack;
  SDL_Rect dstSelect;
  int returning = false;
  SDL_Rect dstHelp1, dstHelp12, dstHelp2, dstHelp22, dstHelp3, dstHelp4, dstHelp5, dstHelp6, dstHelp7;
  TTF_Font *hfont;

  hfont = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 28);
  if (!hfont) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }


  helpSurface1 = loadGetNameRenderedText(hfont, "Breakout is an 'old, but gold' game. To play it, follow the", textcolor);
  helpSurface12 = loadGetNameRenderedText(hfont, "instructions below:", textcolor);
  helpSurface2 = loadGetNameRenderedText(hfont, "To move the bar, you have to use your keyboard's left", textcolor);
  helpSurface22 = loadGetNameRenderedText(hfont, "or right arrow.", textcolor);
  helpSurface3 = loadGetNameRenderedText(hfont, "To throw the ball, just press space.", textcolor);
  helpSurface4 = loadGetNameRenderedText(hfont, "To turn on/off the music, press 'm' on your keyboard.", textcolor);
  helpSurface5 = loadGetNameRenderedText(hfont, "To turn on/off the song, press 's' on your keyboard.", textcolor);
  helpSurface6 = loadGetNameRenderedText(hfont, "To pause the game, press 'p'.", textcolor);
  helpSurface7 = loadGetNameRenderedText(hfont, "And that's all you need to play Breakout! Hope you enjoy it!", textcolor);
  backSurface = loadRenderedText("Back", textcolor);

  dstHelp1.x = 70;
  dstHelp1.y = 75;

  dstHelp12.x = 70;
  dstHelp12.y = 125;

  dstHelp2.x = 70;
  dstHelp2.y = 175;

  dstHelp22.x = 70;
  dstHelp22.y = 225;

  dstHelp3.x = 70;
  dstHelp3.y = 275;

  dstHelp4.x = 70;
  dstHelp4.y = 325;

  dstHelp5.x = 70;
  dstHelp5.y = 375;

  dstHelp6.x = 70;
  dstHelp6.y = 425;

  dstHelp7.x = 70;
  dstHelp7.y = 475;

  dstBack.x = WINDOW_WIDTH/2 - 70;
  dstBack.y = 540;

  dstSelect.x = WINDOW_WIDTH/2 - 90 - SELECT_WIDTH;
  dstSelect.y = 540;

  while(!gQuit && !returning) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
          case SDL_QUIT:
            gQuit = true;
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                gQuit = true;
            }
            else if (e.key.keysym.sym == SDLK_RETURN) {
              returning = true;
            }
      }
    }
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
    if (SDL_BlitSurface(helpSurface1, NULL, gScreenSurface, &dstHelp1) < 0 ||
        SDL_BlitSurface(helpSurface12, NULL, gScreenSurface, &dstHelp12) < 0 ||
        SDL_BlitSurface(helpSurface2, NULL, gScreenSurface, &dstHelp2) < 0 ||
        SDL_BlitSurface(helpSurface22, NULL, gScreenSurface, &dstHelp22) < 0 ||
        SDL_BlitSurface(helpSurface3, NULL, gScreenSurface, &dstHelp3) < 0 ||
        SDL_BlitSurface(helpSurface4, NULL, gScreenSurface, &dstHelp4) < 0 ||
        SDL_BlitSurface(helpSurface5, NULL, gScreenSurface, &dstHelp5) < 0 ||
        SDL_BlitSurface(helpSurface6, NULL, gScreenSurface, &dstHelp6) < 0 ||
        SDL_BlitSurface(helpSurface7, NULL, gScreenSurface, &dstHelp7) < 0 ||
        SDL_BlitSurface(backSurface, NULL, gScreenSurface, &dstBack) < 0 ||
        SDL_BlitSurface(gSelectedOption, NULL, gScreenSurface, &dstSelect) < 0) {
      printf("Error while blitting ranking surface!\n");
      gQuit = true;
    }
    SDL_UpdateWindowSurface(gWindow);
  }
  SDL_FreeSurface(helpSurface1);
  SDL_FreeSurface(helpSurface2);
  SDL_FreeSurface(helpSurface3);
  SDL_FreeSurface(helpSurface4);
  SDL_FreeSurface(helpSurface5);
  SDL_FreeSurface(helpSurface6);
  SDL_FreeSurface(helpSurface7);
  SDL_FreeSurface(backSurface);
  TTF_CloseFont(hfont);
}

int stageThree() {
  OBJECT ball;
  OBJECT bar;
  BLOCK** block;
  SDL_Rect srcBall, dstBall;
  SDL_Rect srcBar, dstBar;
  SDL_Rect dstInGameMenu; /* menu dimensions */
  SDL_Rect dstMusicButton, srcMusicButton;
  SDL_Rect dstSoundButton, srcSoundButton;
  SDL_Color textcolor = {255, 255, 255}; /* sets textcolor as white */
  SDL_Rect dstStage;
  SDL_Surface *stageSurface;
  SDL_Surface *pauseSurface;
  SDL_Rect dstPause;
  TTF_Font *font;
  SDL_Rect dstPoints;
  char points[40];
  char npoints[10];
  SDL_Rect dstLifes;
  char lifes[40];
  char nlifes[4];
  SDL_Rect dstBlocks;
  char blocks[40];
  char nblocks[5];
  int gameStarted = false; /*verify if space bar have already been pressed to start the game*/
  int i, j;
  SDL_Event e;
  int quantBlocks = 0;
  int pausedGame = false;
  int bonus = false;
  OBJECT npcBar;
  SDL_Rect srcNpcBar, dstNpcBar;
  SDL_Surface *inGamePoints;
  SDL_Surface *inGameLife;
  SDL_Surface *inGameBlocks;
  Mix_VolumeMusic(VOLUME);

  if (!loadInGameMenu()) {
    printf("Unable to load text media!\n");
  }
  font = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 55);
  if (!font) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }

  /*create NULL blocks */
  block = (BLOCK**) calloc(ROWS, sizeof(BLOCK*));
  if (!block) gQuit = true;
  for (i = 0; i < ROWS; i++){
    block[i] = (BLOCK*) calloc(COLUMNS, sizeof(BLOCK));
    if (!block[i]) gQuit = true;
  }

  ball = createOBJECT(SCREEN_WIDTH/2 - BALL_WIDTH/2, SCREEN_HEIGHT - 100 - BALL_HEIGHT, 0, 0, gBallSurface);
  bar = createOBJECT(SCREEN_WIDTH/2 - BAR_WIDTH/2, SCREEN_HEIGHT - 100, 0, 0, gBarSurface);
  /* create a non-player Bar */
  npcBar = createOBJECT(SCREEN_WIDTH/2 - BAR_WIDTH/2, SCREEN_HEIGHT - 180, NPCBAR_SPEED, 0, gNpcBarSurface);

  for (i = 0; i < ROWS ; i++) {
    for (j = 0; j < COLUMNS ; j++) {
      if (((i == 1 || i == 6) && j>0 && j<6) ||
         ((j == 1 || j == 5) && i > 1 && i < 6)){
        block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 2, rand()%5);
        quantBlocks++;
      }
      if (i > 1 && i < 6 && j > 1 && j < 5){
        if (((i == 3 || i == 4) && (j == 2 || j == 4))) {
          block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 1, RED);
          quantBlocks++;
        }
        else {
          block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 2, rand()%5);
          quantBlocks++;
        }
      }
      if (i == 7 || i == 8 || i == 9) {
        if ((i+j)%2 == 1) {
          block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 2, rand()%5);
          quantBlocks++;
        }
        else {
          block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 1, RED);
          quantBlocks++;
        }
      }
      if ((i == 0 || i == 1) && (j == 0 || j == 6)){
        block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 2, rand()%5);
        quantBlocks++;
      }
    }
  }

  while (!gQuit){
    while(SDL_PollEvent(&e) != 0) {
      keyPressed(&ball, &bar, e, &gameStarted, pausedGame);
      quitPressed(e);
      turnSound(e);
      turnMusic(e, 3);
      pause(&ball, &bar, &npcBar, e, &pausedGame);
    }
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x66, 0xFF, 0xFF));
    dstInGameMenu.x = SCREEN_WIDTH;
    dstInGameMenu.y = 0;
    dstInGameMenu.h = WINDOW_HEIGHT;
    dstInGameMenu.w = WINDOW_WIDTH - SCREEN_WIDTH;
    SDL_FillRect(gScreenSurface, &dstInGameMenu, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));

    stageSurface = loadRenderedText("Final Stage", textcolor);
    pauseSurface = pausedGame? loadGetNameRenderedText(font, "GAME PAUSED", textcolor): NULL;

    strcpy(points, "Points: ");
    sprintf(npoints, "%d", gPoints);
    strcat(points, npoints);
    inGamePoints = loadRenderedText(points, textcolor);

    strcpy(lifes, "Lifes: ");
    sprintf(nlifes, "%d", gLifes);
    strcat(lifes, nlifes);
    inGameLife = loadRenderedText(lifes, textcolor);

    strcpy(blocks, "Blocks left: ");
    sprintf(nblocks, "%d", quantBlocks);
    strcat(blocks, nblocks);
    inGameBlocks = loadRenderedText(blocks, textcolor);

    moveNPCBAR(&npcBar);
    moveBAR(&bar, &ball, gameStarted);
    moveOBJECT(&ball);

    for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLUMNS; j++) {
        collisionBlock(&block[i][j], &ball, &quantBlocks);
      }
    }

    loseLife(&ball, &bar, &gameStarted);

    if (gLifes <= 0) {
      SDL_FreeSurface(stageSurface);
      SDL_FreeSurface(pauseSurface);
      SDL_FreeSurface(inGameLife);
      SDL_FreeSurface(inGamePoints);
      SDL_FreeSurface(inGameBlocks);
      return 0;
    }
    collisionBar(bar, &ball);
    collisionNpcBar(npcBar, &ball);

    /* ball's source */
    switch (gBallColor) {
      case 0:
        srcBall.x = 0;
        srcBall.y = 0;
        break;
      case 1:
        srcBall.x = BALL_WIDTH;
        srcBall.y = 0;
        break;
      case 2:
        srcBall.x = 0;
        srcBall.y = BALL_HEIGHT;
        break;
      case 3:
        srcBall.x = BALL_WIDTH;
        srcBall.y = BALL_HEIGHT;
        break;
    }
    srcBall.w = BALL_WIDTH;
    srcBall.h = BALL_HEIGHT;
    dstBall.x = ball.posX;
    dstBall.y = ball.posY;

    /* bar's source */
    switch (gBarColor) {
      case 0:
        srcBar.x = 0;
        srcBar.y = 0;
        break;
      case 1:
        srcBar.x = BAR_WIDTH;
        srcBar.y = 0;
        break;
      case 2:
        srcBar.x = 0;
        srcBar.y = BAR_HEIGHT;
        break;
      case 3:
        srcBar.x = BAR_WIDTH;
        srcBar.y = BAR_HEIGHT;
        break;
    }
    srcBar.w = BAR_WIDTH;
    srcBar.h = BAR_HEIGHT;
    dstBar.x = bar.posX;
    dstBar.y = bar.posY;

    /* non-player bar's source */
    srcNpcBar.x = 0;
    srcNpcBar.y = 0;
    srcNpcBar.w = BAR_WIDTH;
    srcNpcBar.h = BAR_HEIGHT;
    dstNpcBar.x = npcBar.posX;
    dstNpcBar.y = npcBar.posY;

    dstStage.x = SCREEN_WIDTH + 30;
    dstStage.y = 30;

    dstPause.x = SCREEN_WIDTH/2 - 170;
    dstPause.y = SCREEN_HEIGHT/2;

    dstPoints.x = SCREEN_WIDTH + 30;
    dstPoints.y = 130;

    dstLifes.x = SCREEN_WIDTH + 30;
    dstLifes.y = 230;

    dstBlocks.x = SCREEN_WIDTH + 30;
    dstBlocks.y = 330;

    dstMusicButton.x = SCREEN_WIDTH + 30;
    dstMusicButton.y = 430;
    srcMusicButton.w = BUTTON_WIDTH;
    srcMusicButton.h = BUTTON_HEIGHT;
    srcMusicButton.y = 0;
    srcMusicButton.x = gMusicCondition? 0 : BUTTON_WIDTH;

    dstSoundButton.x = SCREEN_WIDTH + 60 + BUTTON_WIDTH;
    dstSoundButton.y = 430;
    srcSoundButton.w = BUTTON_WIDTH;
    srcSoundButton.h = BUTTON_HEIGHT;
    srcSoundButton.y = 0;
    srcSoundButton.x = gSoundCondition? 0 : BUTTON_WIDTH;

    for (j = 0; j < COLUMNS; j++) {
      for (i = 0; i < ROWS; i++) {
        if (block[i][j].resistance > 0) drawBlock(block[i][j]);
      }
    }

    if(SDL_BlitSurface(ball.image, &srcBall, gScreenSurface, &dstBall) < 0 ||
        SDL_BlitSurface(bar.image, &srcBar, gScreenSurface, &dstBar) < 0 ||
        SDL_BlitSurface(npcBar.image, &srcNpcBar, gScreenSurface, &dstNpcBar) < 0 ||
        SDL_BlitSurface(stageSurface, NULL, gScreenSurface, &dstStage) < 0 ||
        SDL_BlitSurface(inGameLife, NULL, gScreenSurface, &dstLifes) < 0 ||
        SDL_BlitSurface(inGameBlocks, NULL, gScreenSurface, &dstBlocks) < 0 ||
        SDL_BlitSurface(inGamePoints, NULL, gScreenSurface, &dstPoints) < 0 ||
        SDL_BlitSurface(gMusicButton, &srcMusicButton, gScreenSurface, &dstMusicButton) < 0 ||
        SDL_BlitSurface(gSoundButton, &srcSoundButton, gScreenSurface, &dstSoundButton) < 0) {
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
    }
    if (pausedGame) {
      if (SDL_BlitSurface(pauseSurface, NULL, gScreenSurface, &dstPause) < 0){
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
      }
    }

    /* Update the surface */
    SDL_UpdateWindowSurface(gWindow);

    if (quantBlocks == 0){
      gPoints += 1000;
      SDL_FreeSurface(stageSurface);
      SDL_FreeSurface(pauseSurface);
      SDL_FreeSurface(inGameLife);
      SDL_FreeSurface(inGamePoints);
      SDL_FreeSurface(inGameBlocks);
      return 1;
    }
    if (gPoints%9900 == 0) bonus = false;
    if (gPoints%10000 == 0 && gPoints != 0 && !bonus) {
      gLifes++;
      bonus = true;
    }

    SDL_Delay(time_left());
    next_time += TICK_INTERVAL;
  }
  SDL_FreeSurface(stageSurface);
  SDL_FreeSurface(pauseSurface);
  SDL_FreeSurface(inGameLife);
  SDL_FreeSurface(inGamePoints);
  SDL_FreeSurface(inGameBlocks);
  return 0;
}

int stageTwo() {
  OBJECT ball;
  OBJECT bar;
  BLOCK** block;
  SDL_Rect srcBall, dstBall;
  SDL_Rect srcBar, dstBar;
  SDL_Rect dstInGameMenu; /* menu dimensions */
  SDL_Rect dstMusicButton, srcMusicButton;
  SDL_Rect dstSoundButton, srcSoundButton;
  SDL_Color textcolor = {255, 255, 255}; /* sets textcolor as white */
  SDL_Rect dstStage;
  SDL_Surface *stageSurface;
  SDL_Surface *pauseSurface;
  SDL_Rect dstPause;
  TTF_Font *font;
  SDL_Rect dstPoints;
  char points[40];
  char npoints[10];
  SDL_Rect dstLifes;
  char lifes[40];
  char nlifes[4];
  SDL_Rect dstBlocks;
  char blocks[40];
  char nblocks[5];
  int gameStarted = false; /*verify if space bar have already been pressed to start the game*/
  int i, j;
  SDL_Event e;
  int quantBlocks = 0;
  int pausedGame = false;
  int bonus = false;
  SDL_Surface *inGamePoints;
  SDL_Surface *inGameLife;
  SDL_Surface *inGameBlocks;
  Mix_VolumeMusic(VOLUME);
  return 1;
  
  if (!loadInGameMenu()) {
    printf("Unable to load text media!\n");
  }
  font = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 55);
  if (!font) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }

  /*create NULL blocks */
  block = (BLOCK**) calloc(ROWS, sizeof(BLOCK*));
  if (!block) gQuit = true;
  for (i = 0; i < ROWS; i++){
    block[i] = (BLOCK*) calloc(COLUMNS, sizeof(BLOCK));
    if (!block[i]) gQuit = true;
  }

  ball = createOBJECT(SCREEN_WIDTH/2 - BALL_WIDTH/2, SCREEN_HEIGHT - 100 - BALL_HEIGHT, 0, 0, gBallSurface);
  /* create bar object */
  bar = createOBJECT(SCREEN_WIDTH/2 - BAR_WIDTH/2, SCREEN_HEIGHT - 100, 0, 0, gBarSurface);

  for (i = 0; i < 8; i++) {
    for (j = 0; j < COLUMNS; j++) {
      if ((i%2==0 && j%2==1) || (i%2==1 && j%2==0)) {
        block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 1, rand()%4);
        quantBlocks++;
      }
    }

  }
  for (j = 0; j < COLUMNS; j++){
    i = 9;
    block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 2, PURPLE);
    quantBlocks++;
  }

  /*if (gMusicCondition) {
    Mix_PlayMusic(gStageTwoMusic, -1);
  };*/

  while (!gQuit){
    while(SDL_PollEvent(&e) != 0) {
      keyPressed(&ball, &bar, e, &gameStarted, pausedGame);
      quitPressed(e);
      turnSound(e);
      turnMusic(e, 2);
      pause(&ball, &bar, &bar, e, &pausedGame);
    }

    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x66, 0xFF, 0xFF));
    dstInGameMenu.x = SCREEN_WIDTH;
    dstInGameMenu.y = 0;
    dstInGameMenu.h = WINDOW_HEIGHT;
    dstInGameMenu.w = WINDOW_WIDTH - SCREEN_WIDTH;
    SDL_FillRect(gScreenSurface, &dstInGameMenu, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));

    stageSurface = loadRenderedText("Stage Two", textcolor);
    pauseSurface = pausedGame? loadGetNameRenderedText(font, "GAME PAUSED", textcolor): NULL;

    strcpy(points, "Points: ");
    sprintf(npoints, "%d", gPoints);
    strcat(points, npoints);
    inGamePoints = loadRenderedText(points, textcolor);

    strcpy(lifes, "Lifes: ");
    sprintf(nlifes, "%d", gLifes);
    strcat(lifes, nlifes);
    inGameLife = loadRenderedText(lifes, textcolor);

    strcpy(blocks, "Blocks left: ");
    sprintf(nblocks, "%d", quantBlocks);
    strcat(blocks, nblocks);
    inGameBlocks = loadRenderedText(blocks, textcolor);

    moveBAR(&bar, &ball, gameStarted);
    moveOBJECT(&ball);

    for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLUMNS; j++) {
        collisionBlock(&block[i][j], &ball, &quantBlocks);
      }
    }

    collisionBar(bar, &ball);
    loseLife(&ball, &bar, &gameStarted);

    if (gLifes <= 0) {
      SDL_FreeSurface(stageSurface);
      SDL_FreeSurface(pauseSurface);
      SDL_FreeSurface(inGameLife);
      SDL_FreeSurface(inGamePoints);
      SDL_FreeSurface(inGameBlocks);
      return 0;
    }
    /* ball's source */
    switch (gBallColor) {
      case 0:
        srcBall.x = 0;
        srcBall.y = 0;
        break;
      case 1:
        srcBall.x = BALL_WIDTH;
        srcBall.y = 0;
        break;
      case 2:
        srcBall.x = 0;
        srcBall.y = BALL_HEIGHT;
        break;
      case 3:
        srcBall.x = BALL_WIDTH;
        srcBall.y = BALL_HEIGHT;
        break;
    }
    srcBall.w = BALL_WIDTH;
    srcBall.h = BALL_HEIGHT;
    dstBall.x = ball.posX;
    dstBall.y = ball.posY;

    /* bar's source */
    switch (gBarColor) {
      case 0:
        srcBar.x = 0;
        srcBar.y = 0;
        break;
      case 1:
        srcBar.x = BAR_WIDTH;
        srcBar.y = 0;
        break;
      case 2:
        srcBar.x = 0;
        srcBar.y = BAR_HEIGHT;
        break;
      case 3:
        srcBar.x = BAR_WIDTH;
        srcBar.y = BAR_HEIGHT;
        break;
    }
    srcBar.w = BAR_WIDTH;
    srcBar.h = BAR_HEIGHT;
    dstBar.x = bar.posX;
    dstBar.y = bar.posY;

    dstStage.x = SCREEN_WIDTH + 30;
    dstStage.y = 30;

    dstPause.x = SCREEN_WIDTH/2 - 170;
    dstPause.y = SCREEN_HEIGHT/2;

    dstPoints.x = SCREEN_WIDTH + 30;
    dstPoints.y = 130;

    dstLifes.x = SCREEN_WIDTH + 30;
    dstLifes.y = 230;

    dstBlocks.x = SCREEN_WIDTH + 30;
    dstBlocks.y = 330;

    dstMusicButton.x = SCREEN_WIDTH + 30;
    dstMusicButton.y = 430;
    srcMusicButton.w = BUTTON_WIDTH;
    srcMusicButton.h = BUTTON_HEIGHT;
    srcMusicButton.y = 0;
    srcMusicButton.x = gMusicCondition? 0 : BUTTON_WIDTH;

    dstSoundButton.x = SCREEN_WIDTH + 60 + BUTTON_WIDTH;
    dstSoundButton.y = 430;
    srcSoundButton.w = BUTTON_WIDTH;
    srcSoundButton.h = BUTTON_HEIGHT;
    srcSoundButton.y = 0;
    srcSoundButton.x = gSoundCondition? 0 : BUTTON_WIDTH;

    for (j = 0; j < COLUMNS; j++) {
      for (i = 0; i < ROWS; i++) {
        if (block[i][j].resistance > 0) drawBlock(block[i][j]);
      }
    }

    if(SDL_BlitSurface(ball.image, &srcBall, gScreenSurface, &dstBall) < 0 ||
      SDL_BlitSurface(bar.image, &srcBar, gScreenSurface, &dstBar) < 0 ||
      SDL_BlitSurface(stageSurface, NULL, gScreenSurface, &dstStage) < 0 ||
      SDL_BlitSurface(inGameLife, NULL, gScreenSurface, &dstLifes) < 0 ||
      SDL_BlitSurface(inGameBlocks, NULL, gScreenSurface, &dstBlocks) < 0 ||
      SDL_BlitSurface(inGamePoints, NULL, gScreenSurface, &dstPoints) < 0 ||
      SDL_BlitSurface(gMusicButton, &srcMusicButton, gScreenSurface, &dstMusicButton) < 0 ||
      SDL_BlitSurface(gSoundButton, &srcSoundButton, gScreenSurface, &dstSoundButton) < 0) {
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
    }
    if (pausedGame) {
      if (SDL_BlitSurface(pauseSurface, NULL, gScreenSurface, &dstPause) < 0){
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
      }
    }

    /* Update the surface */
    SDL_UpdateWindowSurface(gWindow);

    if (quantBlocks == 0){
      gPoints += 1000;
      /*Mix_HaltMusic();*/
      SDL_FreeSurface(stageSurface);
      SDL_FreeSurface(pauseSurface);
      SDL_FreeSurface(inGameLife);
      SDL_FreeSurface(inGamePoints);
      SDL_FreeSurface(inGameBlocks);
      return 1;
    }
    if (gPoints%9900 == 0) bonus = false;
    if (gPoints%10000 == 0 && gPoints != 0 && !bonus) {
      gLifes++;
      bonus = true;
    }

    SDL_Delay(time_left());
    next_time += TICK_INTERVAL;
  }
  SDL_FreeSurface(stageSurface);
  SDL_FreeSurface(pauseSurface);
  SDL_FreeSurface(inGameLife);
  SDL_FreeSurface(inGamePoints);
  SDL_FreeSurface(inGameBlocks);
  return 0;
}

int stageOne() {
  OBJECT ball;
  OBJECT bar;
  BLOCK** block;
  SDL_Rect srcBall, dstBall;
  SDL_Rect srcBar, dstBar;
  SDL_Rect dstInGameMenu; /* menu dimensions */
  SDL_Rect dstMusicButton, srcMusicButton;
  SDL_Rect dstSoundButton, srcSoundButton;
  SDL_Color textcolor = {255, 255, 255}; /* sets textcolor as white */
  SDL_Surface *stageSurface;
  SDL_Rect dstStage;
  SDL_Surface *pauseSurface;
  SDL_Rect dstPause;
  TTF_Font *font;
  SDL_Rect dstPoints;
  char points[40];
  char npoints[10];
  SDL_Rect dstLifes;
  char lifes[40];
  char nlifes[4];
  SDL_Rect dstBlocks;
  char blocks[40];
  char nblocks[5];
  int gameStarted = false; /*verify if space bar has already been pressed to start the game*/
  int i, j;
  SDL_Event e;
  int quantBlocks = 0;
  gLifes = 3;
  gPoints = 0;
  int pausedGame = false;
  int bonus = false;
  Mix_VolumeMusic(VOLUME);
  SDL_Surface *inGamePoints;
  SDL_Surface *inGameLife;
  SDL_Surface *inGameBlocks;
  return 1;

  if (!loadInGameMenu()) {
    printf("Unable to load text media!\n");
  }

  font = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 55);
  if (!font) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }

  /*create NULL blocks */
  block = (BLOCK**) calloc(ROWS, sizeof(BLOCK*));
  if (!block) gQuit = true;
  for (i = 0; i < ROWS; i++){
    block[i] = (BLOCK*) calloc(COLUMNS, sizeof(BLOCK));
    if (!block[i]) gQuit = true;
  }

  ball = createOBJECT(SCREEN_WIDTH/2 - BALL_WIDTH/2, SCREEN_HEIGHT - 100 - BALL_HEIGHT, 0, 0, gBallSurface);
  /* create bar object */
  bar = createOBJECT(SCREEN_WIDTH/2 - BAR_WIDTH/2, SCREEN_HEIGHT - 100, 0, 0, gBarSurface);

  for (i = 0; i < 5; i++) {
    for (j = 0; j < COLUMNS; j++) {
      block[i][j] = createBLOCK( BLOCK_WIDTH * j, BLOCK_HEIGHT * i, gBlockSurface, 1, i);
      quantBlocks++;
    }
  }

  if (gMusicCondition) {
    Mix_PlayMusic(gStageOneMusic, -1);
  };

  /* Starts game main loop */
  while (!gQuit){
    /* verifies if any key have been pressed */
    while(SDL_PollEvent(&e) != 0) {
      quitPressed(e);
      turnSound(e);
      turnMusic(e, 1);
      pause(&ball, &bar, &bar, e, &pausedGame);
      keyPressed(&ball, &bar, e, &gameStarted, pausedGame);
    }
    /* Fill screen surface with white */
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x66, 0xFF, 0xFF));
    dstInGameMenu.x = SCREEN_WIDTH;
    dstInGameMenu.y = 0;
    dstInGameMenu.h = WINDOW_HEIGHT;
    dstInGameMenu.w = WINDOW_WIDTH - SCREEN_WIDTH;
    SDL_FillRect(gScreenSurface, &dstInGameMenu, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));

    stageSurface = loadRenderedText("Stage One", textcolor);
    pauseSurface = pausedGame? loadGetNameRenderedText(font, "GAME PAUSED", textcolor): NULL;

    strcpy(points, "Points: ");
    sprintf(npoints, "%d", gPoints);
    strcat(points, npoints);
    inGamePoints = loadRenderedText(points, textcolor);

    strcpy(lifes, "Lifes: ");
    sprintf(nlifes, "%d", gLifes);
    strcat(lifes, nlifes);
    inGameLife = loadRenderedText(lifes, textcolor);

    strcpy(blocks, "Blocks left: ");
    sprintf(nblocks, "%d", quantBlocks);
    strcat(blocks, nblocks);
    inGameBlocks = loadRenderedText(blocks, textcolor);

    moveBAR(&bar, &ball, gameStarted);
    moveOBJECT(&ball);

    /* check collision between ball and all the blocks */
    for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLUMNS; j++) {
        collisionBlock(&block[i][j], &ball, &quantBlocks);
      }
    }

    /* check collision between ball and bar */
    collisionBar(bar, &ball);

    loseLife(&ball, &bar, &gameStarted);

    if (gLifes <= 0) {
      SDL_FreeSurface(stageSurface);
      SDL_FreeSurface(pauseSurface);
      SDL_FreeSurface(inGameLife);
      SDL_FreeSurface(inGamePoints);
      SDL_FreeSurface(inGameBlocks);
      return 0;
    }
    /* ball's source */
    switch (gBallColor) {
      case 0:
        srcBall.x = 0;
        srcBall.y = 0;
        break;
      case 1:
        srcBall.x = BALL_WIDTH;
        srcBall.y = 0;
        break;
      case 2:
        srcBall.x = 0;
        srcBall.y = BALL_HEIGHT;
        break;
      case 3:
        srcBall.x = BALL_WIDTH;
        srcBall.y = BALL_HEIGHT;
        break;
    }
    srcBall.w = BALL_WIDTH;
    srcBall.h = BALL_HEIGHT;
    dstBall.x = ball.posX;
    dstBall.y = ball.posY;

    /* bar's source */
    switch (gBarColor) {
      case 0:
        srcBar.x = 0;
        srcBar.y = 0;
        break;
      case 1:
        srcBar.x = BAR_WIDTH;
        srcBar.y = 0;
        break;
      case 2:
        srcBar.x = 0;
        srcBar.y = BAR_HEIGHT;
        break;
      case 3:
        srcBar.x = BAR_WIDTH;
        srcBar.y = BAR_HEIGHT;
        break;
    }
    srcBar.w = BAR_WIDTH;
    srcBar.h = BAR_HEIGHT;
    dstBar.x = bar.posX;
    dstBar.y = bar.posY;

    dstStage.x = SCREEN_WIDTH + 30;
    dstStage.y = 30;

    dstPause.x = SCREEN_WIDTH/2 - 170;
    dstPause.y = SCREEN_HEIGHT/2;

    dstPoints.x = SCREEN_WIDTH + 30;
    dstPoints.y = 130;

    dstLifes.x = SCREEN_WIDTH + 30;
    dstLifes.y = 230;

    dstBlocks.x = SCREEN_WIDTH + 30;
    dstBlocks.y = 330;

    dstMusicButton.x = SCREEN_WIDTH + 30;
    dstMusicButton.y = 430;
    srcMusicButton.w = BUTTON_WIDTH;
    srcMusicButton.h = BUTTON_HEIGHT;
    srcMusicButton.y = 0;
    srcMusicButton.x = gMusicCondition? 0 : BUTTON_WIDTH;

    dstSoundButton.x = SCREEN_WIDTH + 60 + BUTTON_WIDTH;
    dstSoundButton.y = 430;
    srcSoundButton.w = BUTTON_WIDTH;
    srcSoundButton.h = BUTTON_HEIGHT;
    srcSoundButton.y = 0;
    srcSoundButton.x = gSoundCondition? 0 : BUTTON_WIDTH;

    for (j = 0; j < COLUMNS; j++) {
      for (i = 0; i < ROWS; i++) {
        if (block[i][j].resistance > 0) drawBlock(block[i][j]);
      }
    }

    if(SDL_BlitSurface(ball.image, &srcBall, gScreenSurface, &dstBall) < 0 ||
      SDL_BlitSurface(bar.image, &srcBar, gScreenSurface, &dstBar) < 0 ||
      SDL_BlitSurface(stageSurface, NULL, gScreenSurface, &dstStage) < 0 ||
      SDL_BlitSurface(inGameLife, NULL, gScreenSurface, &dstLifes) < 0 ||
      SDL_BlitSurface(inGameBlocks, NULL, gScreenSurface, &dstBlocks) < 0 ||
      SDL_BlitSurface(inGamePoints, NULL, gScreenSurface, &dstPoints) < 0 ||
      SDL_BlitSurface(gMusicButton, &srcMusicButton, gScreenSurface, &dstMusicButton) < 0 ||
      SDL_BlitSurface(gSoundButton, &srcSoundButton, gScreenSurface, &dstSoundButton) < 0) {
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
    }

    if (pausedGame) {
      if (SDL_BlitSurface(pauseSurface, NULL, gScreenSurface, &dstPause) < 0){
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
      }
    }

    /* Update the surface */
    SDL_UpdateWindowSurface(gWindow);

    if (quantBlocks == 0) {
      gPoints += 1000;
      Mix_HaltMusic();
      SDL_FreeSurface(stageSurface);
      SDL_FreeSurface(pauseSurface);
      SDL_FreeSurface(inGameLife);
      SDL_FreeSurface(inGamePoints);
      SDL_FreeSurface(inGameBlocks);
      return 1;
    }
    if (gPoints%9900 == 0) bonus = false;
    if (gPoints%10000 == 0 && gPoints != 0 && !bonus) {
      gLifes++;
      bonus = true;
    }

    SDL_Delay(time_left());
    next_time += TICK_INTERVAL;
  }
  SDL_FreeSurface(stageSurface);
  SDL_FreeSurface(pauseSurface);
  SDL_FreeSurface(inGameLife);
  SDL_FreeSurface(inGamePoints);
  SDL_FreeSurface(inGameBlocks);
  return 0;
}

void getPlayerName(char *jogador) {
  SDL_Rect dstGetName, dstCongrats;
  SDL_Surface *getName = NULL;
  SDL_Surface *congrats = NULL;
  SDL_Color textcolor = {255, 255, 255};
  SDL_Event e;
  SDL_Rect dstwriteName;
  SDL_Surface *writeName = NULL;
  int returning = false;
  /*char jogador[21];*/
  TTF_Font *font = NULL;

  font = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 35);
  if (!font) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
    gQuit = true;
  }

  SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
  congrats = loadGetNameRenderedText(font, "Congratulations! You set a new record!", textcolor);
  getName = loadGetNameRenderedText(font, "Please, enter your name.", textcolor);

  dstCongrats.x = WINDOW_WIDTH/2 - 300;
  dstCongrats.y = WINDOW_HEIGHT/2 - 150;

  dstGetName.x = WINDOW_WIDTH/2 - 300;
  dstGetName.y = WINDOW_HEIGHT/2 - 100;


  if (SDL_BlitSurface(congrats, NULL, gScreenSurface, &dstCongrats) < 0 ||
      SDL_BlitSurface(getName, NULL, gScreenSurface, &dstGetName) < 0) {
    printf("Error while blitting the surface\n");
  }

  gFont = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 28);
  if (!gFont) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
    gQuit = true;
  }

  dstwriteName.x = WINDOW_WIDTH/2 - 300;
  dstwriteName.y = WINDOW_HEIGHT/2;
  dstwriteName.w = 200;
  dstwriteName.h = 100;

  strcpy(jogador, "\0");

  while (!gQuit && returning == false) {
    if (strlen(jogador) < 20) {
      while (SDL_PollEvent(&e) != 0) {
        switch(e.type) {
          case SDL_QUIT:
            if (strlen(jogador) == 0) strcat(jogador, "UNKNOWN");
            gQuit = true;
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_RETURN) {
              if (strlen(jogador) == 0) strcat(jogador, "UNKNOWN");
              returning = true;
            }
            else if (e.key.keysym.sym == SDLK_ESCAPE) {
              if (strlen(jogador) == 0) strcat(jogador, "UNKNOWN");
              gQuit = true;
            }
            else if (e.key.keysym.sym == SDLK_SPACE) {
              strcat(jogador, " ");
            }
            else if (e.key.keysym.sym == SDLK_a) {
              strcat(jogador, "A");
            }
            else if (e.key.keysym.sym == SDLK_b) {
              strcat(jogador, "B");
            }
            else if (e.key.keysym.sym == SDLK_c) {
              strcat(jogador, "C");
            }
            else if (e.key.keysym.sym == SDLK_d) {
              strcat(jogador, "D");
            }
            else if (e.key.keysym.sym == SDLK_e) {
              strcat(jogador, "E");
            }
            else if (e.key.keysym.sym == SDLK_f) {
              strcat(jogador, "F");
            }
            else if (e.key.keysym.sym == SDLK_g) {
              strcat(jogador, "G");
            }
            else if (e.key.keysym.sym == SDLK_h) {
              strcat(jogador, "H");
            }
            else if (e.key.keysym.sym == SDLK_i) {
              strcat(jogador, "I");
            }
            else if (e.key.keysym.sym == SDLK_j) {
              strcat(jogador, "J");
            }
            else if (e.key.keysym.sym == SDLK_k) {
              strcat(jogador, "K");
            }
            else if (e.key.keysym.sym == SDLK_l) {
              strcat(jogador, "L");
            }
            else if (e.key.keysym.sym == SDLK_m) {
              strcat(jogador, "M");
            }
            else if (e.key.keysym.sym == SDLK_n) {
              strcat(jogador, "N");
            }
            else if (e.key.keysym.sym == SDLK_o) {
              strcat(jogador, "O");
            }
            else if (e.key.keysym.sym == SDLK_p) {
              strcat(jogador, "P");
            }
            else if (e.key.keysym.sym == SDLK_q) {
              strcat(jogador, "Q");
            }
            else if (e.key.keysym.sym == SDLK_r) {
              strcat(jogador, "R");
            }
            else if (e.key.keysym.sym == SDLK_s) {
              strcat(jogador, "S");
            }
            else if (e.key.keysym.sym == SDLK_t) {
              strcat(jogador, "T");
            }
            else if (e.key.keysym.sym == SDLK_u) {
              strcat(jogador, "U");
            }
            else if (e.key.keysym.sym == SDLK_v) {
              strcat(jogador, "V");
            }
            else if (e.key.keysym.sym == SDLK_w) {
              strcat(jogador, "W");
            }
            else if (e.key.keysym.sym == SDLK_x) {
              strcat(jogador, "X");
            }
            else if (e.key.keysym.sym == SDLK_y) {
              strcat(jogador, "Y");
            }
            else if (e.key.keysym.sym == SDLK_z) {
              strcat(jogador, "Z");
            }
            else if (e.key.keysym.sym == SDLK_BACKSPACE) {
              if (strlen(jogador) > 0) {
                jogador[strlen(jogador)-1] = 0;
                SDL_FillRect(gScreenSurface, &dstwriteName, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
              }
              else {
                jogador = jogador; /* trying to avoid unnecessary prints on terminal */
              }
            }
            else {
              jogador = jogador; /* trying to avoid unnecessary prints on terminal */
            }
            break;
        }
        if (strlen(jogador) > 0) {
          writeName = loadRenderedText(jogador, textcolor);
          if (SDL_BlitSurface(writeName, NULL, gScreenSurface, &dstwriteName) < 0) {
            printf("Error while blitting the surface\n");
          }
        }
      }
    }
    else {
      while (SDL_PollEvent(&e) != 0) {
        switch(e.type) {
          case SDL_QUIT:
            gQuit = true;
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_RETURN) {
              returning = true;
            }
            else if (e.key.keysym.sym == SDLK_BACKSPACE) {
              if (strlen(jogador) > 0) {
                jogador[strlen(jogador)-1] = 0;
                SDL_FillRect(gScreenSurface, &dstwriteName, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
              }
              else {
                jogador = jogador; /* trying to avoid unnecessary prints on terminal */
              }
            }
            writeName = loadRenderedText(jogador, textcolor);
            if (SDL_BlitSurface(writeName, NULL, gScreenSurface, &dstwriteName) < 0) {
              printf("Error while blitting the surface\n");
            }
        }
      }
    }
    SDL_UpdateWindowSurface(gWindow);
  }
  SDL_FreeSurface(congrats);
  SDL_FreeSurface(getName);
  SDL_FreeSurface(writeName);
  TTF_CloseFont(font);
}

void ranking() {
  SDL_Rect dstRanking;
  SDL_Event e;
  int returning = false;
  SDL_Color textcolor = {255, 255, 255};
  FILE* parq;
  PLAYER records[5];
  SDL_Surface* name[5];
  SDL_Surface* pontuation[5];
  SDL_Surface* backSurface;
  SDL_Surface* rankingText = NULL;
  SDL_Rect dstName[5];
  SDL_Rect dstPoints[5];
  SDL_Rect dstBack;
  SDL_Rect dstSelect;
  char nPoints[10];
  int i;

  parq = fopen(".rankings.bin", "r");
  if (!parq) {
    printf("Failed to read ranking.\n");
    gQuit = true;
  }
  fread(records, sizeof(PLAYER), 5, parq);
  for (i = 0; i < 5; i++) {
    name[i] = loadRenderedText(records[i].name, textcolor);
    sprintf(nPoints, "%9d", records[i].points);
    pontuation[i] = loadRenderedText(nPoints, textcolor);
  }

  for (i = 0; i < 5; i++) {
    dstName[i].x = WINDOW_WIDTH/2 - 300;
    dstName[i].y = 200 + 50*i;
    dstPoints[i].x = WINDOW_WIDTH/2 + 200;
    dstPoints[i].y = 200 + 50*i;
  }

  rankingText = loadRenderedText("Ranking", textcolor);
  backSurface = loadRenderedText("Back", textcolor);
  if (!rankingText || !backSurface) {
    printf("Failed to render text! Error: %s\n", TTF_GetError());
    gQuit = true;
  }

  dstRanking.x = WINDOW_WIDTH/2 - 100;
  dstRanking.y = 100;
  dstBack.x = WINDOW_WIDTH/2 - 70;
  dstBack.y = 450;
  dstSelect.x = WINDOW_WIDTH/2 - 90 - SELECT_WIDTH;
  dstSelect.y = 450;

  while(!gQuit && !returning) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
          case SDL_QUIT:
            gQuit = true;
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                gQuit = true;
            }
            else if (e.key.keysym.sym == SDLK_RETURN) {
              returning = true;
            }
          }
      }
      SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
      if (SDL_BlitSurface(rankingText, NULL, gScreenSurface, &dstRanking) < 0 ||
          SDL_BlitSurface(backSurface, NULL, gScreenSurface, &dstBack) < 0 ||
          SDL_BlitSurface(gSelectedOption, NULL, gScreenSurface, &dstSelect) < 0) {
        printf("Error while blitting ranking surface!\n");
        gQuit = true;
      }
      for (i = 0; i < 5; i++) {
        if (SDL_BlitSurface(name[i], NULL, gScreenSurface, &dstName[i]) < 0 ||
            SDL_BlitSurface(pontuation[i], NULL, gScreenSurface, &dstPoints[i]) < 0) {
          printf("Error while blitting ranking surface!\n");
          gQuit = true;
        }
      }
      SDL_UpdateWindowSurface(gWindow);
  }
  for (i = 0; i < 5; i++) {
    SDL_FreeSurface(name[i]);
    SDL_FreeSurface(pontuation[i]);
  }
  SDL_FreeSurface(backSurface);
  SDL_FreeSurface(rankingText);
}

int makeRank() {
  FILE *pRankFile;
  PLAYER jogador;
  PLAYER recordistas[5];
  PLAYER aux;
  int i;

  jogador.points = gPoints;

  pRankFile = fopen(".rankings.bin", "r+");
  if(!pRankFile) {
    perror("Could not open the rankings file! Error: ");
    gQuit = true;
  }
  else {
    fread(recordistas, sizeof(PLAYER), 5, pRankFile);
    /* Searches for values in the top 5 ranks that are lower than the
       the new player score. */

    if(recordistas[4].points < jogador.points) {
      getPlayerName(&*(jogador.name));
      recordistas[4] = jogador;
      for (i = 4; i > 0; i--) {
        if (recordistas[i].points > recordistas[i-1].points) {
          aux = recordistas[i];
          recordistas[i] = recordistas[i-1];
          recordistas[i-1] = aux;
        }
      }
      fclose(pRankFile);
      pRankFile = fopen(".rankings.bin", "wb");
      if(!pRankFile){
        perror("Ranking file could not be replaced! Error: ");
        gQuit = true;
      }
      else {
        fwrite(recordistas, sizeof(PLAYER), 5, pRankFile);
        fclose(pRankFile);
        return 1;
      }
    }
    else return 0;
  }
  return 1;
}

void menu() {
  unsigned int cursor = 0;
  SDL_Event e;
  SDL_Rect dstMenu;
  SDL_Rect dstSelect;

  dstMenu.x = 0;
  dstMenu.y = 0;

  /*if (!loadTextMedia()) {
    printf("Could not load text media!\n");
    gQuit = true;
  }*/

  gFont = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 28);
  if (!gFont) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }

  while (!gQuit) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
        case SDL_QUIT:
          gQuit = true;
          break;
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_RETURN) {
            switch(cursor) {
              case 0:
                if (stageOne()) {
                  if (stageTwo()) {
                    stageThree();
                  }
                }
                if (!gQuit) {
                  if (makeRank()){
                    ranking();
                  }
                  else gameOver();
                }
                break;
              case 1:
                ranking();
                break;
              case 2:
                settings();
                break;
              case 3:
                help();
                break;
              case 4:
                gQuit = true;
                break;
            }
          }
          else if (e.key.keysym.sym == SDLK_ESCAPE) {
            gQuit = true;
          }
          else if (e.key.keysym.sym == SDLK_DOWN) {
            cursor = (cursor + 1)%5; /* using %4 to make sure the cursor doesn't stop at the top/bottom */
          }
          else if (e.key.keysym.sym == SDLK_UP) {
            cursor = (cursor + 4)%5;
          }
          break;
      }
      switch(cursor) {
        case 0:
          dstSelect.y = 235;
          break;
        case 1:
          dstSelect.y = 305;
          break;
        case 2:
          dstSelect.y = 375;
          break;
        case 3:
          dstSelect.y = 445;
          break;
        case 4:
          dstSelect.y = 515;
          break;
      }
      dstSelect.x = 310;
      if (SDL_BlitSurface(gMenuSurface, NULL, gScreenSurface, &dstMenu) < 0 ||
          SDL_BlitSurface(gSelectedOption, NULL, gScreenSurface, &dstSelect) < 0) {
        printf("Error while blitting ranking surface!\n");
      }
      SDL_UpdateWindowSurface(gWindow);
    }
  }
}

void gameOver() {
  SDL_Surface *overSurface;
  SDL_Surface *backSurface;
  SDL_Rect dstOver;
  TTF_Font *font;
  SDL_Color textcolor = {255, 255, 255};
  SDL_Event e;
  SDL_Rect dstBack;
  SDL_Rect dstSelect;

  font = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 45);
  if (!font) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
  }
  overSurface = loadGetNameRenderedText(font, "Game Over!", textcolor);
  backSurface = loadGetNameRenderedText(font, "Back", textcolor);

  dstOver.x = WINDOW_WIDTH/2 - 100;
  dstOver.y = WINDOW_HEIGHT/2 - 150;

  dstBack.x = WINDOW_WIDTH/2 - 70;
  dstBack.y = 540;

  dstSelect.x = WINDOW_WIDTH/2 - 90 - SELECT_WIDTH;
  dstSelect.y = 540;

  while(!gQuit) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
          case SDL_QUIT:
            gQuit = true;
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                gQuit = true;
            }
            else if (e.key.keysym.sym == SDLK_RETURN) {
              menu();
            }
      }
    }
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
    if (SDL_BlitSurface(overSurface, NULL, gScreenSurface, &dstOver) < 0 ||
        SDL_BlitSurface(backSurface, NULL, gScreenSurface, &dstBack) < 0 ||
        SDL_BlitSurface(gSelectedOption, NULL, gScreenSurface, &dstSelect) < 0) {
      printf("Error while blitting ranking surface!\n");
      gQuit = true;
    }
    SDL_UpdateWindowSurface(gWindow);
  }
  SDL_FreeSurface(overSurface);
  SDL_FreeSurface(backSurface);
  TTF_CloseFont(font);
}
