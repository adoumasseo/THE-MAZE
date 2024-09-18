#include "../inc/header.h"

/**
 * main - entry point of the program
 * Return: 0 on succes and negative value if not
 */
int main(void)
{
	SDL_Event e;
	char timeText[10];
	int sec, min;

	quit = 0;
	load_map_from_file();
	find_exit_wall();
	init_player_base_position();
	set_player_pos();
	init();
	Mix_PlayMusic(bg_music, -1);
	Timer_Start();
	while (!quit)
	{
		min = ((120000 - Timer_GetTicks()) / 1000) / 60;
		sec = ((120000 - Timer_GetTicks()) / 1000) % 60;
		check_escape_time(e);
		while (SDL_PollEvent(&e))
		{
			if (can_exit() && handle_quit())
			{
				exit_prompt("YOU WIN :)", "PRESS SPACE TO QUIT");
				handle_win_exit(e);
			}
			else if (handle_quit())
			{
				Timer_Pause();
				exit_prompt("WANT TO QUIT ?", "Y TO QUIT AND N TO CONTINUE");
				handle_confirm_quit(e);
			}
			handle_key_input();
			handle_mouse_input();
		}
		snprintf(timeText, sizeof(timeText), "%02u:%02us", min, sec);
		draw_ATH();
		RenderText("TIME", textColor, 5, 560);
		draw_rect(5, 600, 125, 40);
		RenderText(timeText, textColor, 10, 600);
		cast_rays();
		SDL_RenderPresent(gRenderer);
	}
	free_close();
	return (0);
}
