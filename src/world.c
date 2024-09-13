#include "../inc/header.h"


/**
 * drax_celling - draw the celling
 * Return: Nothing
 */
void draw_celling(int index, int wtp)
{
	/* Draw celling */
	SDL_SetRenderDrawColor(gRenderer, 85, 129, 149, 255);
	SDL_RenderDrawLine(gRenderer, index, 0, index, wtp);
}

/**
 * draw_floor - draw the floor
 * Return: Nothing
 */
void draw_floor(int index, int wbp)
{
	/* Draw floor*/
	SDL_SetRenderDrawColor(gRenderer, 28, 40, 51, 255);
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
 */
void draw_world(double rx, double ry, double px,
		double py, double ra, double pa, int index)
{
	int wallTopPixel, wallBottomPixel;
	float distanceToWall, wallHeight;
	const double projectionPlaneDist = (screenWidth / 2) / tan(FOV / 2);
	Uint32 drawColor, texel;
	Uint8 r, g, b, a;
	float hitX;
	int texX, texY, y;

	distanceToWall = sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py));
	distanceToWall *= cos(ra - pa); /*eyefish effect */
	wallHeight = (projectionPlaneDist * cellSize) / distanceToWall;
	wallTopPixel = (screenHeight / 2) - (wallHeight / 2);
	wallBottomPixel = (screenHeight / 2) + (wallHeight / 2);

	draw_celling(index, wallTopPixel);
	draw_floor(index, wallBottomPixel);

	if (hitVertical)
		hitX = (ry - (int)ry) * wall.w;
	else
		hitX = (rx - (int)rx) * wall.w;
	texX = (int)(hitX) % wall.w;

	for (y = wallTopPixel; y < wallBottomPixel; y++)
	{
		texY = (y - wallTopPixel) * ((float)wall.h / wallHeight);
		texel = wall.texture_buffer[(texY * wall.w) + texX];
		// drawColor = handle_light_effect(texel, distanceToWall);
		r = (texel >> 24) & 0xFF;
		g = (texel >> 16) & 0xFF;
		b = (texel >> 8) & 0xFF;
		a = texel & 0xFF;
		SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
		/* Draw the vertical line representing the wall slice */
		SDL_RenderDrawLine(gRenderer, index, wallTopPixel, index, wallBottomPixel);
	}
}
