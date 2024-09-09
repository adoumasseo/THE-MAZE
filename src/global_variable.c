#include "../inc/header.h"

/* SDL STUFF*/
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
/* ATH viewport: assign in init.c*/
SDL_Rect ath_viewport;
/* Game viewport: assing in init.c*/
SDL_Rect game_viewport;
/* screen bounds: assign in init.c */
int screenWidth;
int screenHeight;
/* Map initialisation: assig using load_map_from_file in map.c*/
int worldMap[mapWidth][mapHeight];
/* Player Position*/
SDL_Rect player;
double px = mapWidth * cellSize - 35;
double py = mapHeight * cellSize - 35;
double pdx;/*assign in player.c draw_player() */
double pdy;/*assign in player.c draw_player() */
double playerAngle = 4.5;
