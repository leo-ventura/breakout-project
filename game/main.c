#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "defs.h"
#include "global.h"
#include "functions.h"

int main(int argc, char const *argv[]) {
  /* local variables */

  /* Start up SDL and create window */
  if (!init())  {
      printf("SDL could not be initialized\n");
  }
  else {
    if (!loadMedia()) {
      printf("Media could not be loaded\n");
    }
    else {
      /* MAIN MENU CODE HERE */
      /*menu();*/

      gQuit = false;
      stageOne();
      stageTwo();
      stageThree();
      }
    }
    closing();
    return 0;
}
