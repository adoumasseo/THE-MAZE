#include "../inc/header.h"

/**
* is_wall - a fct to check if there is colision with the wall
* @x: the player x position
* @y: the player y position
* Return: Positive integer if there is collision and 0 if not
*/
int is_wall(float x, float y)
{
	int gridX = (int)(x / cellSize);
	int gridY = (int)(y / cellSize);

	if (gridX >= 0 && gridY >= 0 && gridX < mapWidth && gridY < mapHeight)
	{
		return (worldMap[gridY][gridX]);
	}
	return (0);
}

/**
 * getScreenBound - a fct that initialize the screen Bounds
 * Return: Nothing it's void type function
 */
void getScreenBound(void)
{
	SDL_Rect displayBounds;

	SDL_GetDisplayBounds(0, &displayBounds);
	screenWidth = displayBounds.w;
	screenHeight = displayBounds.h;
}

/**
 * handle_light_effect - handle the light based on a factor
 * Description: This factor is compute using the distance between the
 * player and the walls and also an const
 * 
 * @wallColor: The color using to draw the wall
 * @distance: The distance between the player and the wall
 * Return: The emphasis to draw the wall in
 */
Uint32 handle_light_effect(Uint32 wallColor, float distance)
{
	float factor = 1 - (distance / distance_bf_dark);
	Uint8 r, g, b, a;

	if (factor < 0)
		factor = 0;
	if (factor > 1)
		factor = 1;
	r = (wallColor >> 24) & 0xFF;
	g = (wallColor >> 16) & 0xFF;
	b = (wallColor >> 8)& 0xFF;
	a = wallColor & 0xFF;

	r *= factor;
    g *= factor;
    b *= factor;

	return ((r << 24) | (g << 16) | (b << 8) | a);

}