#include "../inc/header.h"

/**
 * main - entry point of the program
 * @argc: Number of argument of the program
 * @argv: An array that contains the arguments
 * Return: 0 on succes and negative value if not
 */
int main(int argc, char *argv[])
{
	SDL_Event e;
	int quit = 0;

	if (argc < 2)
	{
		printf("Usage: %s <map file> \n", argv[0]);
		return (-1);
	}
	if (!load_map_from_file(argv[1]))
	{
		printf("Unable to load the map \n");
		return (-1);
	}
	if (init() < 0)
	{
		printf("Something fail in the init\n");
		return (-1);
	}
	else
	{
		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = 1;
				if (handle_quit())
					quit = 1;
				handle_key_input();
				handle_mouse_input();
			}
			create_viewport();
			/*draw_map();*/
			cast_rays();
			/*Update the screen */
			SDL_RenderPresent(gRenderer);
		}
	}
	free_close();
	return (0);
}
