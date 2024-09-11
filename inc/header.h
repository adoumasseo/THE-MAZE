#ifndef MAIN_H
#define MAIN_H

	#include "stdio.h"
	#include "SDL2/SDL.h"
	#include <stddef.h>
	#include <math.h>

	#define mapWidth 24
	#define mapHeight 24
	#define cellSize 8
	#define rotationSpeed 0.1
	#define moveSpeed 0.8
	#define FOV (60 * M_PI / 180)
	#define NUM_RAYS screenWidth
	#define distance_bf_dark 400

	extern SDL_Window *gWindow;

	extern SDL_Renderer *gRenderer;

	extern SDL_Rect ath_viewport;
	extern SDL_Rect game_viewport;

	/* Player Position */
	extern SDL_Rect player;
	extern double px;
	extern double py;
	extern double playerAngle;
	extern double pdx;
	extern double pdy;
	extern int worldMap[mapWidth][mapHeight];

	extern int screenWidth;
	extern int screenHeight;

	extern int hitVertical;

	void getScreenBound(void);
	int init(void);
	void free_close(void);
	void draw_map(void);
	void create_viewport(void);
	void draw_player(void);
	void handle_key_input(void);
	void handle_mouse_input(void);
	void cast_rays(void);
	void draw_world(double rx, double ry, double px,
			double py, double ra, double pa, int index);
	int is_wall(float x, float y);
	Uint32 handle_light_effect(Uint32 wallColor, float distance);
	int load_map_from_file(const char *filename);
	void print_array(void);
	int handle_quit(void);
	void set_hitVertical(float rx, float ry);
#endif
