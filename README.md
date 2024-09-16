
# MAZE - The RENEWALLS

The Maze is a 3D Maze game that uses ray casting to render a 2D map into a 3D navigable world!
Here is the context: <br>
Every time you launch the program you land in one of the 10 random maps available. You have a compass, a drawing of the map and the time that passes. Your goal is to find the exit drawn in green on the map and in the 3D rendering as quickly as possible. Eventually I would like there to be a timer and when you reach the time limit without finding the exit you lose the game. Basically it's a kind of escape game without the textures.

<br>
<br>
The work is not finished, I am still working on it and for the moment I am using the C library and SDL2. The development was done with Ubuntu 23.04 LTS - gcc

### About SDL2 

Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It is used by video playback software, emulators, and popular games including Valve's award winning catalog and many Humble Bundle games.

### Prerequisites
This is the default for Ubuntu users. If you don't use it, you'll have to do some research to install them on your operating system.
<br>
You need to have SDL2, SDL2_image and SDL2_ttf install on your machine.
In case you haven't installed them yet you can use the ```install.sh``` file in the root of the project to install them with the command
```sh
$ ./install.sh
```
### Instalation
Clone this repository with the command:
```sh
$ git clone https://github.com/adoumasseo/THE-MAZE.git
```
After the clone move to THE-MAZE directory
```sh
$ cd THE-MAZE
```

Now use this command
```sh
$ gcc -o raycaster ./src/*  -lSDL2 -lSDL2_ttf -lm 
```
when the compilation proccess end use this command and you can test the game
```sh
$ ./raycaster
```
Here is some images of the actual gameplay:
![IMAGE 1](https://github.com/adoumasseo/THE-MAZE/blob/main/assets/images/image1.png)
![IMAGE 2](https://github.com/adoumasseo/THE-MAZE/blob/main/assets/images/image2.png)
![IMAGE 3](https://github.com/adoumasseo/THE-MAZE/blob/main/assets/images/image3.png)

