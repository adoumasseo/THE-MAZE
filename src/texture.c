#include "../inc/header.h"

/**
 * load_texture_with_upng - load walls and exitWall into their GV
 * Return: On success 1 on failure 0
 */
int load_texture_with_upng(void)
{
	int succes_status = 1;
	upng_t *upng_wall = upng_new_from_file("./assets/images/wall.png");
	upng_t *upng_exit = upng_new_from_file("./assets/images/exit.png");

	if (upng_wall == NULL || upng_exit == NULL)
	{
		printf("Enable to load IMG %d\n %d\n", upng_get_error(upng_wall),
						upng_get_error(upng_exit));
		succes_status = 0;
	}
	else
	{
		upng_decode(upng_wall);
		upng_decode(upng_exit);
		if (upng_get_error(upng_wall) == UPNG_EOK &&
			upng_get_error(upng_exit) == UPNG_EOK)
		{
			wall.w = upng_get_width(upng_wall);
			wall.h = upng_get_height(upng_wall);
			wall.upng_texture = upng_wall;
			wall.texture_buffer = (Uint32 *)upng_get_buffer(upng_wall);
			exitWall.w = upng_get_width(upng_exit);
			exitWall.h = upng_get_height(upng_exit);
			exitWall.upng_texture = upng_exit;
			exitWall.texture_buffer = (Uint32 *)upng_get_buffer(upng_exit);
		}
		else
		{
			printf("Unable to decode the two textures %d\n %d\n",
				upng_get_error(upng_wall), upng_get_error(upng_exit));
			succes_status = 0;
		}
	}
	return (succes_status);
}

/**
 * free_texture_of_upng - free the texture i load from upng
 * Return: Nothing it's void type function
 */
void free_texture_of_upng(void)
{
	upng_free(wall.upng_texture);
	upng_free(exitWall.upng_texture);
}

/**
 * print_texture - print the texture load for debugging purpose
 * Return: Nothing it's void type function
 */
void print_texture(void)
{
	printf("Image Wall wth: %d\n Image wall hgt: %d\n", wall.w, wall.h);
	printf("Image ext wdh: %d\n Image ext hgt: %d\n", exitWall.w, exitWall.h);
}