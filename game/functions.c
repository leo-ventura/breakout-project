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

double distance(double x1, double y1, double x2, double y2){
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
            Mix_PlayChannel(-1, gDestroyBlockSound, 0);
          }
          else {
            Mix_PlayChannel(-1, gCollisionBlockSound, 0);
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
              Mix_PlayChannel(-1, gDestroyBlockSound, 0);
            }
            else {
              Mix_PlayChannel(-1, gCollisionBlockSound, 0);
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
        Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        Mix_PlayChannel(-1, gCollisionBlockSound, 0);
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
        Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        Mix_PlayChannel(-1, gCollisionBlockSound, 0);
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
        Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        Mix_PlayChannel(-1, gCollisionBlockSound, 0);
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
        Mix_PlayChannel(-1, gDestroyBlockSound, 0);
      }
      else {
        Mix_PlayChannel(-1, gCollisionBlockSound, 0);
      }
    }
  }
}

void collisionNpcBar(OBJECT bar, OBJECT *ball) {
  /* up and down */
  if (((ball->posY == bar.posY + BAR_HEIGHT) ||
      (ball->posY + BALL_HEIGHT == bar.posY)) &&
      (ball->posX + BALL_WIDTH/2 > bar.posX) &&
      (ball->posX + BALL_WIDTH/2 < bar.posX + BAR_WIDTH)){
        ball->stepY *= -1;
        ball->posY += ball->stepY;
  }
  /* right and left */
  else if (((ball->posX <= bar.posX + BAR_WIDTH && ball->posX > bar.posX) ||
       (ball->posX + BALL_WIDTH >= bar.posX && ball->posX + BALL_WIDTH < bar.posX + BAR_WIDTH )) &&
       (ball->posY + BALL_HEIGHT/2 > bar.posY) &&
       (ball->posY + BALL_HEIGHT/2 < bar.posY + BAR_HEIGHT)){
          ball->stepX *= -1;
          ball->posX += ball->stepX;
  }
  /* upper left */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX, bar.posY) < BALL_WIDTH/2){
    if (ball->stepX > 0) {
      ball->stepX *= -1;
    }
    if (ball->stepY > 0) {
      ball->stepY *= -1;
    }
    ball->posX += ball->stepX;
    ball->posY += ball->stepY;
  }

  /* lower left */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX, bar.posY + BAR_HEIGHT) < BALL_WIDTH/2){
    if (ball->stepX > 0) {
      ball->stepX *= -1;
    }
    if (ball->stepY < 0) {
      ball->stepY *= -1;
    }
    ball->posX += ball->stepX;
    ball->posY += ball->stepY;
  }

  /* lower right */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX + BAR_WIDTH, bar.posY + BAR_HEIGHT) < BALL_WIDTH/2){
    if (ball->stepX < 0) {
      ball->stepX *= -1;
    }
    if (ball->stepY < 0) {
      ball->stepY *= -1;
    }
    ball->posX += ball->stepX;
    ball->posY += ball->stepY;
  }

  /* upper right */
  else if (distance(ball->posX + BALL_WIDTH/2, ball->posY + BALL_HEIGHT/2, bar.posX + BAR_WIDTH, bar.posY) < BALL_WIDTH/2){
    if (ball->stepX < 0) {
      ball->stepX *= -1;
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
        ){
          ball->stepY *= -1;
          ball->stepX = ((ball->posX + BALL_WIDTH/2) - (bar.posX + BAR_WIDTH/2))/40;
          ball->posY += ball->stepY;
          ball->posX += ball->stepX;
          Mix_PlayChannel(-1, gCollisionBarSound, 0);
    }
    else if (((ball->posX <= bar.posX + BAR_WIDTH && ball->posX > bar.posX) ||
         (ball->posX + BALL_WIDTH >= bar.posX && ball->posX + BALL_WIDTH < bar.posX + BAR_WIDTH )) &&
         (ball->posY + BALL_HEIGHT/2 > bar.posY) &&
         (ball->posY + BALL_HEIGHT/2 < bar.posY + BAR_HEIGHT)){
           ball->stepX = ((ball->posX + BALL_WIDTH/2) - (bar.posX + BAR_WIDTH/2))/40;
           ball->posY += ball->stepY;
           ball->posX += ball->stepX;
           Mix_PlayChannel(-1, gCollisionBarSound, 0);
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

void gameOver(OBJECT *ball, OBJECT *bar, int *gameStarted){
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
    printf("%d Lifes\n", gLifes);
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

  /* free the texture from other textures */
  /*freeTexture(texture);*/

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

int loadTextMedia() {
  int success = true;
/*  SDL_Color blacktextcolor = {0, 0, 0};*/
  SDL_Color whitetextcolor = {255, 255, 255};

  gFont = TTF_OpenFont("../image_library/alagard_BitFont.ttf", 35);
  if (!gFont) {
    printf("Failed to load font! Error: %s\n", TTF_GetError());
    success = false;
  }
  gRankingText = loadRenderedText("Ranking", whitetextcolor);
  gMenuText = loadRenderedText("Menu", whitetextcolor);
  if (!gRankingText || !gMenuText) {
    printf("Failed to render text! Error: %s\n", TTF_GetError());
    success = false;
  }
  return success;
}

int loadMedia() {
    /*Loading success flag*/
    int success = true;
    /*uint32_t colorKey;*/

    /*Load ball surface*/
    gBallSurface = loadSurface("../image_library/bola.png");
    SDL_SetColorKey( gBallSurface, SDL_TRUE, SDL_MapRGB( gBallSurface->format, 0xFF, 0xFF, 0xFF ) );

    /* load bar surface */
    gBarSurface = loadSurface("../image_library/bar.png");

    /* load block surface */
    gBlockSurface = loadSurface("../image_library/block.png");

    /* non-player bar */
    gNpcBarSurface = loadSurface("../image_library/bar.png");

    if(!gBallSurface || !gBlockSurface || !gBarSurface || !gNpcBarSurface) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    /*load sounds */
    gCollisionBarSound = Mix_LoadWAV("../sound_library/collisionBar.wav");
    gCollisionBlockSound = Mix_LoadWAV("../sound_library/collisionBlock.wav");
    gDestroyBlockSound = Mix_LoadWAV("../sound_library/destroyBlock.wav");

    if (!gCollisionBlockSound || !gCollisionBarSound || !gDestroyBlockSound) {
      printf("Failed to load sounds! SDL Error: %s\n", SDL_GetError());
      success = false;
    }

    return success;
}

void closing() {
    /*Free ball image*/
    SDL_FreeSurface(gBallSurface);
    gBallSurface = NULL;

    /* Close font */
    TTF_CloseFont(gFont);
    gFont = NULL;

    /* Free fonts' surface */
    SDL_FreeSurface(gRankingText);
    SDL_FreeSurface(gMenuText);

    /* Free bar image */
    SDL_FreeSurface(gBarSurface);
    gBarSurface = NULL;

    /* Free block surface */
    SDL_FreeSurface(gBlockSurface);
    gBlockSurface = NULL;

    /* Free npcBar surface */
    SDL_FreeSurface(gNpcBarSurface);
    gNpcBarSurface = NULL;

    /*Destroy window*/
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    /*Free sounds */
    Mix_FreeChunk(gCollisionBarSound);
    Mix_FreeChunk(gCollisionBlockSound);
    Mix_FreeChunk(gDestroyBlockSound);

    /*Quit SDL subsystems*/
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void keyPressed(OBJECT *ball, OBJECT *bar, SDL_Event e, int *gameStarted){
  switch(e.type) {
      case SDL_QUIT:
        gQuit = true;
        break;
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE) {
            gQuit = true;
        }
        else if(!*gameStarted) {
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

void options() {
  printf("Entrei em Options\n");
}

void help() {
  printf("Entrei em Help\n");
}

void stageThree() {
  OBJECT ball;
  OBJECT bar;
  BLOCK** block;
  SDL_Rect srcBall, dstBall;
  SDL_Rect srcBar, dstBar;
  int gameStarted = false; /*verify if space bar have already been pressed to start the game*/
  int i, j;
  SDL_Event e;
  int quantBlocks = 0;
  OBJECT npcBar;
  SDL_Rect srcNpcBar, dstNpcBar;


  /*create NULL blocks */
  block = (BLOCK**) calloc(ROWS, sizeof(BLOCK*));
  for (i = 0; i < ROWS; i++){
    block[i] = (BLOCK*) calloc(COLUMNS, sizeof(BLOCK));
  }

  ball = createOBJECT(SCREEN_WIDTH/2 - BALL_WIDTH/2, SCREEN_HEIGHT - 100 - BALL_HEIGHT, 0, 0, gBallSurface);
  bar = createOBJECT(SCREEN_WIDTH/2 - BAR_WIDTH/2, SCREEN_HEIGHT - 100, 0, 0, gBarSurface);
  /* create a non-player Bar */
  npcBar = createOBJECT(SCREEN_WIDTH/2 - BAR_WIDTH/2, SCREEN_HEIGHT - 180, 1.3, 0, gNpcBarSurface);

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
  printf("%d blocks\n", quantBlocks);



  while (!gQuit){
    while(SDL_PollEvent(&e) != 0) {
        keyPressed(&ball, &bar, e, &gameStarted);
    }
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x66, 0xFF, 0xFF));

    moveNPCBAR(&npcBar);
    moveBAR(&bar, &ball, gameStarted);
    moveOBJECT(&ball);

    for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLUMNS; j++) {
        collisionBlock(&block[i][j], &ball, &quantBlocks);
      }
    }
    gameOver(&ball, &bar, &gameStarted);
    if (gLifes < 0) gQuit = true;

    collisionBar(bar, &ball);
    collisionNpcBar(npcBar, &ball);

    srcBall.x = 0;
    srcBall.y = 0;
    srcBall.w = BALL_WIDTH;
    srcBall.h = BALL_HEIGHT;
    dstBall.x = ball.posX;
    dstBall.y = ball.posY;

    /* bar's source */
    srcBar.x = 0;
    srcBar.y = 0;
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


    for (j = 0; j < COLUMNS; j++) {
      for (i = 0; i < ROWS; i++) {
        if (block[i][j].resistance > 0) drawBlock(block[i][j]);
      }
    }

    if(SDL_BlitSurface(ball.image, &srcBall, gScreenSurface, &dstBall) < 0 ||
      SDL_BlitSurface(bar.image, &srcBar, gScreenSurface, &dstBar) < 0 ||
      SDL_BlitSurface(npcBar.image, &srcNpcBar, gScreenSurface, &dstNpcBar) < 0) {
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
    }

    /* Update the surface */
    SDL_UpdateWindowSurface(gWindow);

    /* it'll be changed later */
    SDL_Delay(2.5);
    if (quantBlocks == 0){
      gPoints += 1000;
      /*return;*/
      stageThree();
    }
    if (gPoints%10000 == 0 && gPoints != 0) gLifes++;
  }
}

void stageTwo() {
  OBJECT ball;
  OBJECT bar;
  BLOCK** block;
  SDL_Rect srcBall, dstBall;
  SDL_Rect srcBar, dstBar;
  int gameStarted = false; /*verify if space bar have already been pressed to start the game*/
  int i, j;
  SDL_Event e;
  int quantBlocks = 0;

  /*create NULL blocks */
  block = (BLOCK**) calloc(ROWS, sizeof(BLOCK*));
  for (i = 0; i < ROWS; i++){
    block[i] = (BLOCK*) calloc(COLUMNS, sizeof(BLOCK));
  }

  ball = createOBJECT(SCREEN_WIDTH/2 - BALL_WIDTH/2, SCREEN_HEIGHT - 100 - BALL_HEIGHT, 0, 0, gBallSurface);
  /* create bar object */
  bar = createOBJECT(SCREEN_WIDTH/2 - BAR_WIDTH/2, SCREEN_HEIGHT - 100, 0, 0, gBarSurface);

  printf("%d blocks\n", quantBlocks);
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

  printf("%d blocks\n", quantBlocks);
  while (!gQuit){
    while(SDL_PollEvent(&e) != 0) {
        keyPressed(&ball, &bar, e, &gameStarted);
    }

    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x66, 0xFF, 0xFF));
    moveBAR(&bar, &ball, gameStarted);
    moveOBJECT(&ball);

    for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLUMNS; j++) {
        collisionBlock(&block[i][j], &ball, &quantBlocks);
      }
    }

    collisionBar(bar, &ball);
    gameOver(&ball, &bar, &gameStarted);
    if (gLifes < 0) gQuit = true;


    srcBall.x = 0;
    srcBall.y = 0;
    srcBall.w = BALL_WIDTH;
    srcBall.h = BALL_HEIGHT;
    dstBall.x = ball.posX;
    dstBall.y = ball.posY;

    /* bar's source */
    srcBar.x = 0;
    srcBar.y = 0;
    srcBar.w = BAR_WIDTH;
    srcBar.h = BAR_HEIGHT;
    dstBar.x = bar.posX;
    dstBar.y = bar.posY;

    for (j = 0; j < COLUMNS; j++) {
      for (i = 0; i < ROWS; i++) {
        if (block[i][j].resistance > 0) drawBlock(block[i][j]);
      }
    }

    if(SDL_BlitSurface(ball.image, &srcBall, gScreenSurface, &dstBall) < 0 ||
      SDL_BlitSurface(bar.image, &srcBar, gScreenSurface, &dstBar) < 0) {
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
    }

    /* Update the surface */
    SDL_UpdateWindowSurface(gWindow);

    /* it'll be changed later */
    SDL_Delay(2.5);
    if (quantBlocks == 0){
      gPoints += 1000;
      /*return;*/
      stageThree();
    }
    if (gPoints%10000 == 0 && gPoints != 0) gLifes++;
  }
}

void stageOne() {
  OBJECT ball;
  OBJECT bar;
  BLOCK** block;
  SDL_Rect srcBall, dstBall;
  SDL_Rect srcBar, dstBar;
  int gameStarted = false; /*verify if space bar has already been pressed to start the game*/
  int i, j;
  SDL_Event e;
  int quantBlocks = 0;

  /*create NULL blocks */
  block = (BLOCK**) calloc(ROWS, sizeof(BLOCK*));
  for (i = 0; i < ROWS; i++){
    block[i] = (BLOCK*) calloc(COLUMNS, sizeof(BLOCK));
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
  printf("%d blocks\n", quantBlocks);

  /* Starts game main loop */
  printf("%d Lifes\n", gLifes);
  while (!gQuit){
    /* verifies if any key have been pressed */
    while(SDL_PollEvent(&e) != 0) {
      keyPressed(&ball, &bar, e, &gameStarted);
    }

        /* Fill screen surface with white */
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x66, 0xFF, 0xFF));

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

    gameOver(&ball, &bar, &gameStarted);
    if (gLifes < 0) gQuit = true;

    /* ball's source */
    srcBall.x = 0;
    srcBall.y = 0;
    srcBall.w = BALL_WIDTH;
    srcBall.h = BALL_HEIGHT;
    dstBall.x = ball.posX;
    dstBall.y = ball.posY;

    /* bar's source */
    srcBar.x = 0;
    srcBar.y = 0;
    srcBar.w = BAR_WIDTH;
    srcBar.h = BAR_HEIGHT;
    dstBar.x = bar.posX;
    dstBar.y = bar.posY;

    for (j = 0; j < COLUMNS; j++) {
      for (i = 0; i < ROWS; i++) {
        if (block[i][j].resistance > 0) drawBlock(block[i][j]);
      }
    }

    if(SDL_BlitSurface(ball.image, &srcBall, gScreenSurface, &dstBall) < 0 ||
      SDL_BlitSurface(bar.image, &srcBar, gScreenSurface, &dstBar) < 0) {
        printf("SDL could not blit! SDL Error: %s\n", SDL_GetError());
        gQuit = true;
    }

    /* Update the surface */
    SDL_UpdateWindowSurface(gWindow);

    /* it'll be changed later */
    SDL_Delay(2.5);
    if (quantBlocks == 0) {
      gPoints += 1000;
      /*return;*/
      stageTwo();
    }
    if (gPoints%10000 == 0 && gPoints != 0) gLifes++;
  }
}

void ranking() {
  SDL_Rect dstRanking;
  SDL_Event e;
  int returning = false;

  dstRanking.x = WINDOW_WIDTH/2 - 100;
  dstRanking.y = 100;

  while(!gQuit && returning == false) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
          case SDL_QUIT:
            gQuit = true;
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                gQuit = true;
            }
            else if (e.key.keysym.sym == SDLK_LEFT) {
              returning = true;
            }
      }
      SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x66, 0xFF, 0xFF));
      if (SDL_BlitSurface(gRankingText, NULL, gScreenSurface, &dstRanking) < 0) {
        printf("Error while blitting ranking surface!\n");
      }
      SDL_UpdateWindowSurface(gWindow);
    }
  }
}

void menu() {
  unsigned int cursor = 0;
  SDL_Event e;
  SDL_Rect dstMenu;
/*  SDL_Rect dstStart;*/
  SDL_Rect dstRanking;
/*  SDL_Rect dstOptions;
  SDL_Rect dstHelp;*/

  dstMenu.x = WINDOW_WIDTH/2 - 100;
  dstMenu.y = 100;

  /*dstStart.x = WINDOW_WIDTH/2 - 100;
  dstStart.y = 200;*/

  dstRanking.x = WINDOW_WIDTH/2 - 100;
  dstRanking.y = 300;

/*  dstOptions.x = WINDOW_WIDTH/2 - 100;
  dstOptions.y = 400;

  dstHelp.x = WINDOW_WIDTH/2 - 100;
  dstHelp.y = 500;
*/
  /* carregar midia do menu */
  if (!loadTextMedia()) {
    printf("Could not load text media!\n");
    gQuit = true;
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
                stageOne();
                break;
              case 1:
                ranking();
                break;
              case 2:
                /*options = true;*/
                options();
                break;
              case 3:
                help();
                /*help = true;*/
                break;
            }
          }
          else if (e.key.keysym.sym == SDLK_ESCAPE) {
            gQuit = true;
          }
          else if (e.key.keysym.sym == SDLK_DOWN) {
            cursor = (cursor + 1)%4; /* using %4 to make sure the cursor doesn't stop at the top/bottom */
            printf("cursor em %d\n", cursor);
          }
          else if (e.key.keysym.sym == SDLK_UP) {
            cursor = (cursor + 3)%4;
            printf("cursor em %d\n", cursor);
          }
          break;
      }
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
    if (SDL_BlitSurface(gMenuText, NULL, gScreenSurface, &dstMenu) < 0 ||
        SDL_BlitSurface(gRankingText, NULL, gScreenSurface, &dstRanking) < 0) {
      printf("Error while blitting menu surface\n");
    }
    SDL_UpdateWindowSurface(gWindow);
    }
  }
}
