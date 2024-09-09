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

/**
 * load_map_from_file - a function to load the map from a file
 * Description: This function uses the path given, opens the file
 * at this map, reads it, and loads it into the worldMap global variable.
 * 
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
        return 0;
    mapFile = fopen(filename, "r");
    if (mapFile == NULL)
    {
        printf("Couldn't open the file: %s\n", filename);
        return 0;
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
        return 0;
    }
    return 1;
}