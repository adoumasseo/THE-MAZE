#ifndef MAIN_H
#define MAIN_H

	#include "stdio.h"
	#include "SDL2/SDL.h"
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_mixer.h> 
	#include <stddef.h>
	#include <stdlib.h>
	#include <time.h>
	#include <math.h>

	#define mapWidth 24
	#define mapHeight 24
	#define cellSize 32
	#define draw_factor 0.25
	#define rotationSpeed 0.1
	#define moveSpeed 1.5
	#define FOV (60 * M_PI / 180)
	#define NUM_RAYS screenWidth
	#define distance_bf_dark 800
	#define distance_around_exit 2

	/*Time handler*/
	typedef struct time_s
	{
		Uint32 startTicks;
		Uint32 pausedTicks;
		int paused;
		int started;
	} Timer;
	extern Timer gameTime;

	/* window & Renderer */
	extern SDL_Window *gWindow;
	extern SDL_Renderer *gRenderer;
	extern SDL_Color textColor;
	extern int quit;

	/*Font*/
	extern TTF_Font *font_prompt_q; /* q for question*/
	extern TTF_Font *font_prompt_o; /* o for options*/

	/*Viewport*/
	extern SDL_Rect ath_viewport;
	extern SDL_Rect game_viewport;

	/* Player Position */
	extern SDL_Rect player;
	extern double px;
	extern double py;
	extern double basepx;
	extern double basepy;
	extern double playerAngle;
	extern double pdx;
	extern double pdy;

	/* Music handler*/
	extern Mix_Music *bg_music;

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
	void draw_celling(int index, int wtp);
	void draw_floor(int index, int wbp);
	int random_int(void);
	char *random_map_path(void);
	int find_color(int x, int y);
	void find_exit_wall(void);
	int can_exit(void);
	int init_font(void);
	void exit_prompt(const char *q, const char *o);
	void handle_confirm_quit(SDL_Event e);
	void handle_win_exit(SDL_Event e);
	void handle_lose_decision(SDL_Event e);
	void draw_ath(void);
	void draw_circle(int x, int y, int radius);
	void draw_cardinal_directions(int x, int y, int radius);
	void draw_player_direction(int x, int y, int radius);
	void render_compass(void);
	void draw_CD_name(void);

	/* Time handler function */
	void Timer_Start(void);
	void Timer_Stop(void);
	void Timer_Pause(void);
	void Timer_Unpause(void);
	Uint32 Timer_GetTicks(void);
	int Timer_IsStarted(void);
	int Timer_IsPaused(void);
	void RenderText(const char *message, SDL_Color color, int x, int y);
	void draw_rect(int x, int y, int w, int h);
	void draw_ATH(void);
	void check_escape_time(SDL_Event e);
	int init_music(void);
	void set_player_pos(void);
#endif
