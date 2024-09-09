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
 * 
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
