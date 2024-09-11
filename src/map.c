#include "../inc/header.h"

/**
 * draw_map - a fct that create an viewport for the map and draw it
 * Return: Positive Integer number on succes and -1 on fail
 */
void draw_map(void)
{
	int i, j;
	SDL_Rect square;

	/* Iterate through the map and draw each cell */
	for (j = 0; j < mapHeight; j++)
	{
		for (i = 0; i < mapWidth; i++)
		{
			/* Define the square's position and size */
			square.x = i * cellSize;
			square.y = j * cellSize;
			square.w = cellSize;
			square.h = cellSize;
			/*Set the draw color based on map value*/
			if (worldMap[j][i] == 0)
				SDL_SetRenderDrawColor(gRenderer,
							0, 0, 0, 255);
			else
				SDL_SetRenderDrawColor(gRenderer,
						255, 255, 255, 255);
			/*Draw the rectangle */
			SDL_RenderFillRect(gRenderer, &square);
			/* Reset the color to gray to draw the line */
			SDL_SetRenderDrawColor(gRenderer, 82, 78, 78, 255);
			SDL_RenderDrawLineF(gRenderer, i * cellSize, 0,
				i * cellSize, mapHeight * cellSize - 1);
		}
		SDL_RenderDrawLine(gRenderer, 0, j * cellSize,
			mapWidth * cellSize - 1, j * cellSize);
	}
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	draw_player();
}

/**
 * cast_rays - a fct that draw the rays
 * Return: Nothing for now
 */
void cast_rays(void)
{
	int i, hitWall, mapX, mapY;
	double rayAngle, rayX, rayY, stepX, stepY;

	for (i = 0; i < NUM_RAYS; i++)
	{
		rayAngle = playerAngle - FOV / 2 + i * (FOV / NUM_RAYS);
		rayX = px;
		rayY = py;
		stepX = cos(rayAngle);
		stepY = sin(rayAngle);
		hitWall = 0;
		while (!hitWall)
		{
			rayX += stepX;
			rayY += stepY;
			mapX = (int)rayX / cellSize;
			mapY = (int)rayY / cellSize;
			if (mapX >= 0 && mapX < mapWidth && mapY >= 0 &&
				mapY < mapHeight && worldMap[mapY][mapX] != 0
				)
			{
				hitWall = 1;
				set_hitVertical(rayX, rayY);
				SDL_RenderSetViewport(gRenderer, &ath_viewport);
				SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(gRenderer, px + cellSize / 2,
						py + cellSize / 2, rayX, rayY);
				SDL_RenderSetViewport(gRenderer, &game_viewport);
				draw_world(rayX, rayY, px, py, rayAngle, playerAngle, i);
			}
		}
	}
}


/**
 * handle_light_effect - handle the light based on a factor
 * Description: This factor is compute using the distance between the
 * player and the walls and also an const
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
	b = (wallColor >> 8) & 0xFF;
	a = wallColor & 0xFF;
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/**
 * load_map_from_file - a function to load the map from a file
 * Description: This function uses the path given, opens the file
 * at this map, reads it, and loads it into the worldMap global variable.
 * @filename: the path of the file that contains the map
 * Return: 1 on success, 0 on failure
 */
int load_map_from_file(const char *filename)
{
	int col, row = 0;
	size_t len;
	FILE *mapFile = NULL;
	char line[mapWidth + 2];

	if (filename == NULL)
		return (0);
	mapFile = fopen(filename, "r");
	if (mapFile == NULL)
	{
		printf("Couldn't open the file: %s\n", filename);
		return (0);
	}
	while (fgets(line, sizeof(line), mapFile) != NULL && row < mapHeight)
	{
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		for (col = 0; col < mapWidth; col++)
		{
			if (line[col] != '0')
				worldMap[row][col] = (int)line[col] - 48;
			else
				worldMap[row][col] = 0;
		}
		row++;
	}
	fclose(mapFile);
	if (row != mapHeight)
	{
		printf("Map file incorrect dimensions.Rows read= %d, expected= %d.\n",
		row, mapHeight);
		return (0);
	}
	return (1);
}
