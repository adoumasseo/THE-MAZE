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
	quit = 0;
	
	if (!load_map_from_file())
	{
		printf("Unable to load the map \n");
		return (-1);
	}
	else
		find_exit_wall();
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
				if (can_exit() && handle_quit())
				{
					exit_prompt("YOU WIN !!",
							"PRESS SPACE TO QUIT");	
					handle_win_exit(e);
				}
				else if (handle_quit())
				{
					exit_prompt("DO YOU WANT TO QUIT THE GAME ??",
							"PRESS Y TO QUIT AND N TO CONTINUE !!");
					handle_confirm_quit(e);
				}
				handle_key_input();
				handle_mouse_input();
			}
			create_viewport();
			draw_map();
			render_compass();
			cast_rays();
			/*Update the screen */
			SDL_RenderPresent(gRenderer);
		}
	}
	/*printf("(%f, %f)\n", px, py);*/
	free_close();
	return (0);
}
