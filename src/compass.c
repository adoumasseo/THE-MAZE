#include "../inc/header.h"

/**
 * drax_circle - a fct to draw the circle of the compass
 * @x: the x coordinate of the circle center
 * @y: the y coordinate of the circle center
 * @radius: the radius of the circle
 * 
 * Return: Nothing
 */
void draw_circle(int x, int y, int radius)
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(gRenderer, x + dx, y + dy);
			}
		}
	}
}

/**
 * draw_cardinal_directions - draw the cardinal direction on the circle
 * @x: the x coordinate of the circle center
 * @y: the y coordinate of the circle center
 * @radius: the radius of the circle
 * 
 * Return: Nothing
 */
void draw_cardinal_directions(int x, int y, int radius)
{
	/*North*/
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(gRenderer, x, y - radius, x, y - radius + 10);

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	/*East*/
	SDL_RenderDrawLine(gRenderer, x + radius, y, x + radius - 10, y);
	// South
	SDL_RenderDrawLine(gRenderer, x, y + radius, x, y + radius - 10);
	// West
	SDL_RenderDrawLine(gRenderer, x - radius, y, x - radius + 10, y);
}

/**
 * draw_player_direction - draw the player angle position
 * @x: the x coordinate of the circle center
 * @y: the y coordinate of the circle center
 * @radius: the radius of the circle
 * 
 * Return: Nothing
 */
void draw_player_direction(int x, int y, int radius)
{
	int directionX = x + (int)(radius * cos(playerAngle));
	int directionY = y + (int)(radius * sin(playerAngle));
	SDL_RenderDrawLine(gRenderer, x, y, directionX, directionY);
}


/**
 * draw_CD_name - use TTF to draw on the screen CD name
 * Description: CD name mean North, East, West South
 * Return: Nothing
 */
void draw_CD_name(void)
{
	int tw, th, i;
	SDL_Rect renderText;
	SDL_Surface *text_s;
	SDL_Texture *text_T;
	SDL_Color textColor = {255, 255, 255};
	const char *directions[4] = {"N", "E", "W", "S"};
	int positions[4][2] =
	{
		{92, 300},
		{175, 385},
		{5, 385},
		{92, 480}
    };
	for (int i = 0; i < 4; i++)
	{
		text_s = TTF_RenderText_Solid(font_prompt_o, directions[i], textColor);
		text_T = SDL_CreateTextureFromSurface(gRenderer, text_s);
		free(text_s);
		SDL_QueryTexture(text_T, NULL, NULL, &tw, &th);
		renderText.x = positions[i][0];
		renderText.y = positions[i][1];
		renderText.w = tw;
		renderText.h = th;

		SDL_RenderCopy(gRenderer, text_T, NULL, &renderText);
		SDL_DestroyTexture(text_T);
	}
}

/**
 * render_compass - draw the compass with the other functions
 * Return: Nothing
 */
void render_compass(void)
{
	int compassX = 100;
	int compassY = 400;
	int radius = 70;

	draw_circle(compassX, compassY, radius);
	draw_cardinal_directions(compassX, compassY, radius);
	draw_player_direction(compassX, compassY, radius);
	draw_CD_name();
}