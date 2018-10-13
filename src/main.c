#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "defs.h"
#include "global.h"
#include "functions.h"

int main(int argc, char const *argv[]) {
  /* Start up SDL and create window */
  srand (time(NULL));
  if (!init())  {
      printf("SDL could not be initialized\n");
  }
  else {
    if (!loadMedia()) {
      printf("Media could not be loaded\n");
    }
    else {
      gQuit = false;
      menu();
    }
  }
  closing();
  return 0;
}
