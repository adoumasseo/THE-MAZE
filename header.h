#ifndef MAIN_H
#define MAIN_H

#include "stdio.h"
#include "SDL2/SDL.h"
#include <stddef.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define cellSize 8

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern SDL_Rect viewport;

/* Player Position */
extern SDL_Rect player;
extern double px;
extern double py;

extern int worldMap[mapWidth][mapHeight];

int init(void);
void free_close(void);
void draw_map(void);
void create_viewport(void);
void draw_player(void);
#endif