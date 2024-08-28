#ifndef MAIN_H
#define MAIN_H

#include "stdio.h"
#include "SDL2/SDL.h"
#include <stddef.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480


extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern SDL_Rect viewport;

extern int worldMap[mapWidth][mapHeight];

int init(void);
void free_close(void);
void draw_map(void);
void create_viewport(void);
#endif