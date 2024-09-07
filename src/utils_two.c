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
