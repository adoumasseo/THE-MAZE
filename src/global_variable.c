#include "../inc/header.h"

/* SDL STUFF*/
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Color textColor = {0, 255, 0, 255};
int quit;

/* Font */
TTF_Font *font_prompt_q;
TTF_Font *font_prompt_o;

/* ATH viewport: assign in init.c*/
SDL_Rect ath_viewport;
/* Game viewport: assing in init.c*/
SDL_Rect game_viewport;

/* screen bounds: assign in init.c */
int screenWidth;
int screenHeight;

/* Map initialisation: assig using load_map_from_file in map.c*/
int worldMap[mapWidth][mapHeight];

/* Exit wall coordinate */
int exit_x, exit_y;

/* Player Position*/
SDL_Rect player;
double px;
double py;
double pdx;/*assign in player.c draw_player() */
double pdy;/*assign in player.c draw_player() */
double playerAngle = 0.0;
double basepx;
double basepy;

int hitVertical = 0; /* Check if a vertical or horizontal wall is hit*/



/* Time handler*/
Timer gameTime = {0, 0, 0, 0};

/* Music handler */
Mix_Music *bg_music;