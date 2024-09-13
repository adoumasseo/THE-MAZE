#ifndef MAIN_H
#define MAIN_H

	#include "stdio.h"
	#include "SDL2/SDL.h"
	#include <stddef.h>
	#include <stdlib.h>
	#include <time.h>
	#include <math.h>
	#include "upng.h"

	#define mapWidth 24
	#define mapHeight 24
	#define cellSize 32
	#define draw_factor 0.25
	#define rotationSpeed 0.1
	#define moveSpeed 2
	#define FOV (60 * M_PI / 180)
	#define NUM_RAYS screenWidth
	#define distance_bf_dark 800
	#define distance_around_exit 2

	/**
	 * struct texture_s - struct for texture
	 * @w: texture width
	 * @h: texture height
	 * @texture_buffer: pointer to texture buffer
	 * @upng_texture: pointer to upng buffer
	 */
	typedef struct texture_s
	{
		int w;
		int h;
		Uint32 *texture_buffer;
		upng_t *upng_texture;
	} texture_t;

	/* window & Renderer */
	extern SDL_Window *gWindow;
	extern SDL_Renderer *gRenderer;

	/*Viewport*/
	extern SDL_Rect ath_viewport;
	extern SDL_Rect game_viewport;

	/* Texture*/
	extern texture_t wall;
	extern texture_t exitWall;

	/* Player Position */
	extern SDL_Rect player;
	extern double px;
	extern double py;
	extern double playerAngle;
	extern double pdx;
	extern double pdy;

	/* Exit wall coordinate */
	extern int exit_x;
	extern int exit_y;

	/* Map */
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
			double py, double ra, double pa,
			int index, int color_code);
	int is_wall(float x, float y);
	Uint32 handle_light_effect(Uint32 wallColor, float distance);
	int load_map_from_file(void);
	void print_array(void);
	int handle_quit(void);
	void set_hitVertical(float rx, float ry);
	int load_texture_with_upng(void);
	void free_texture_of_upng(void);
	void print_texture(void);
	void draw_celling(int index, int wtp);
	void draw_floor(int index, int wbp);
	int random_int(void);
	char *random_map_path(void);
	int find_color(int x, int y);
	void find_exit_wall(void);
	int can_exit(void);
#endif
