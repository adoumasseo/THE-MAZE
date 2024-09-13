#include "../inc/header.h"

/**
 * random_map_path - generate a random map path
 * Description: The path is call random because we gonna use a random int in it
 * Return: The string generate
 */
char *random_map_path(void)
{
	int rand_int = random_int(), i;
	char *str = "./assets/maps/map1.txt";
	long int len = strlen(str);
	char *path = malloc(len);

	if (path == NULL)
	{
		printf("Malloc failed \n");
		return NULL;
	}
	for (i = 0; i < len; i++)
	{
		if (*(str + i) == '1')
			*(path + i) = (rand_int + '0');
		else
			*(path + i) = *(str + i);
	}
	return (path);
}

/**
 * find_color - find the appropriate color to draw a wall
 * @x: mapX from cast_rays in map.c
 * @y: mapY from cast_rays in map.c
 * Return: An integer 1 -> white(wall), 2 -> green(exit)
 */
int find_color(int x, int y)
{
	if (worldMap[y][x] == 1)
		return (1);
	else if (worldMap[y][x] == 2)
		return(2);
}


void find_exit_wall(void)
{
	int j, i;

	for (j = 0; j < mapHeight; j++)
	{
		for (i = 0; i < mapWidth; i++)
		{
			if (worldMap[j][i] == 2)
			{
				exit_x = i;
				exit_y = j;
			}
		}
	}
	printf("(%d, %d)\n", exit_x, exit_y);
}