#include "../inc/header.h"

/**
 * main - entry point of the program
 * @argc: Number of argument of the program
 * @argv: An array that contains the arguments
 * Return: 0 on succes and negative value if not
 */
int main(void)
{
	SDL_Event e;
	SDL_Color textColor = {0, 255, 0, 255};
	Uint32 ct; /*current time*/
	char timeText[10];
	int sec, min;

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
		Timer_Start();
		while (!quit)
		{
			ct = Timer_GetTicks();
			min = (ct / 1000) / 60;
			sec = (ct / 1000) % 60;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = 1;
				if (can_exit() && handle_quit())
				{
					exit_prompt("YOU WIN :)",
							"PRESS SPACE TO QUIT");
					handle_win_exit(e);
				}
				else if (handle_quit())
				{
					Timer_Pause();
					exit_prompt("DO YOU WANT TO QUIT THE GAME ??",
							"PRESS Y TO QUIT AND N TO CONTINUE !!");
					handle_confirm_quit(e);
				}
				handle_key_input();
				handle_mouse_input();
			}
			snprintf(timeText, sizeof(timeText), "%02u:%02us", min, sec);
			create_viewport();
			draw_map();
			render_compass();
			RenderText("TIME", textColor, 5, 560);
			draw_rect(5, 600, 125, 40);
			RenderText(timeText, textColor, 10, 600);
			cast_rays();
			/*Update the screen */
			SDL_RenderPresent(gRenderer);
		}
	}
	free_close();
	return (0);
}
