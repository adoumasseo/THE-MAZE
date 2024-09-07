
# MAZE - The RENEWALLS

The Maze is a 3D Maze game that uses ray casting to render a 2D map into a 3D navigable world!

The work is not finish , I'm still working on it and for know i'm using C and SDL2 library. Deveploment was performed using Ubuntu 23.04 LTS - gcc 

### About SDL2 

Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It is used by video playback software, emulators, and popular games including Valve's award winning catalog and many Humble Bundle games.

## Instalation 
```sh
$ git clone https://github.com/adoumasseo/THE-MAZE.git
```
You need to have SDL2 install on your machine
After the clone move to THE-MAZE directory
```sh
$ cd THE-MAZE
```

Now use this command
```sh
$ gcc -o raycaster ./src/*  -lSDL2 -lm 
```
when the compilation proccess end use this command
```sh
$ ./raycaster
```

