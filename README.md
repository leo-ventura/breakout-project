# Breakout
This is a version of the game Breakout developed by students from Federal University of Rio de Janeiro. To play this game you have to have SDL2 and SDL2 image installed. If you don't know how to do it, check this [link](https://wiki.libsdl.org/Installation).

## Src
The folder where we'll be developing our code. It also contains the makefile you should use to compile the program. If you just want to play the game, all you need is there.

## Testing SDL
This folder is to test whether your SDL2 is working or not.

### SDL2 libraries
- If you're using Windows, you'll need to install the **developer** libraries below according to your architecture and compiler:
  - [SDL2](https://www.libsdl.org/download-2.0.php)
  - [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
  - [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
  - [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

- If you're using Ubuntu, you can install it running on your terminal:
```
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

- If you're an Arch Linux user, you can install it with:
```
sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

### Compilation on Linux
  - To download, compile and run, all you have to do is:
    ```
    git clone https://github.com/leo-ventura/breakout-project.git
    cd breakout-project/src
    make
    ./breakout
    ``` 
