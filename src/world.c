#include "../inc/header.h"


/**
 * draw_celling - draw the celling
 * @index: index
 * @wtp: the top wall
 * Return: Nothing
 */
void draw_celling(int index, int wtp)
{
	/* Draw celling */
	SDL_SetRenderDrawColor(gRenderer, 1, 1, 14, 255);
	SDL_RenderDrawLine(gRenderer, index, 0, index, wtp);
}

/**
 * draw_floor - draw the floor
 * @index: index
 * @wbp: the bottom wall
 * Return: Nothing
 */
void draw_floor(int index, int wbp)
{
	/* Draw floor*/
	SDL_SetRenderDrawColor(gRenderer, 13, 13, 13, 255);
	SDL_RenderDrawLine(gRenderer, index, wbp,
					index, screenHeight);
}

/**
 * draw_world - this draw the world
 * @rx: the ray end x coordinates
 * @ry: the ray en y coordinates
 * @px: the player x coordinates
 * @py: the player y coordinates
 * @ra: the ray angle
 * @pa: the player direction angle
 * @index: the current index in the cast_rays loop
 * @color_code: the color code
 */
void draw_world(double rx, double ry, double px,
			double py, double ra, double pa,
			int index, int color_code)
{
	int wallTopPixel, wallBottomPixel;
	float distanceToWall, wallHeight;
	const double projectionPlaneDist = (screenWidth / 2) / tan(FOV / 2);
	Uint32 drawColor;
	Uint8 r, g, b, a;

	distanceToWall = sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py));
	distanceToWall *= cos(ra - pa); /*eyefish effect */
	wallHeight = (projectionPlaneDist * cellSize) / distanceToWall;
	wallTopPixel = (screenHeight / 2) - (wallHeight / 2);
	wallBottomPixel = (screenHeight / 2) + (wallHeight / 2);

	draw_celling(index, wallTopPixel);
	draw_floor(index, wallBottomPixel);

	if (color_code == 1)
		drawColor = handle_light_effect((150 << 24) | (150 << 16)
					| (150 << 8) | 255, distanceToWall);
	else if (color_code == 2)
		drawColor = handle_light_effect((0 << 24) | (140 << 16)
					| (77 << 8) | 255, distanceToWall);
	r = (drawColor >> 24) & 0xFF;
	g = (drawColor >> 16) & 0xFF;
	b = (drawColor >> 8) & 0xFF;
	a = drawColor & 0xFF;
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);

	/* Draw the vertical line representing the wall slice */
	SDL_RenderDrawLine(gRenderer, index, wallTopPixel,
					index, wallBottomPixel);
}