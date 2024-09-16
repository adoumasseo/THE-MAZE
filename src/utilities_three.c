#include "../inc/header.h"

/**
 * draw_rect - draw a rec based on the arg received
 * @x: x coordinate
 * @y: y coordinate
 * @w: width
 * @h:height
 * Return: Nothing
 */
void draw_rect(int x, int y, int w, int h)
{
	SDL_Rect outlineRect = {x, y, w, h};

	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(gRenderer, &outlineRect);
}

/**
 * draw_ATH - Call of function to draw the primary ATH
 * Return: Nothing
 */
void draw_ATH(void)
{
	create_viewport();
	draw_map();
	render_compass();
}