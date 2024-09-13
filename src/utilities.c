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
 * print_array - this function draw in stdout worldMap
 * Return: Nothing it's void type function
 */
void print_array(void)
{
	int i, j;

	for (i = 0; i < mapHeight; i++)
	{
		for (j = 0; j < mapWidth; j++)
		printf("%d", worldMap[i][j]);
		printf("\n");
	}
	printf("La hauteur est : %d\n", j);
}

/**
 * set_hitVertical - this fct set the global variable hitVertical
 * Description: hitVertical = 1 if it's vertical and 0 else
 * @rx: the current ray x coordinate
 * @ry: the current ray y coordinate
 * Return: Nothing it's void type function
 */
void set_hitVertical(float rx, float ry)
{
	if (fabs(rx - px) > fabs(ry - py))
		hitVertical = 1;
	else
		hitVertical = 0;
}

/**
 * random_int - a fct to generate Random int between 1 & 9
 * Return: The integer generate
 */
int random_int(void)
{
	int min = 1, max = 9;

	srand(time(NULL));
	return (min + rand() % (min - max + 1));
}