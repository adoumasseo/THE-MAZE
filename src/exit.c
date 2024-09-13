#include "../inc/header.h"

/**
 * handle_confirm_quit - wait the user prompt to quit the game
 * @e: The current queue of event
 * Return: Nothing
 */
void handle_confirm_quit(SDL_Event e)
{
	while(SDL_WaitEvent(&e))
	{
		if (e.key.keysym.sym == SDLK_y)
		{
			quit = 1;
			break;
		}
		if (e.key.keysym.sym == SDLK_n)
		{
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
			SDL_RenderClear(gRenderer);
			break;
		}
	}
}

/**
 * exit_prompt - this function handle the exit prompt printing on screen
 * Return: Nothing it's void type function
 */
void exit_prompt(void)
{
	int twq, thq, two, tho;
	SDL_Rect renderQ, renderO;
	SDL_Color textColor = {0, 0, 0}; 
	SDL_Surface* prompt_question_s = TTF_RenderText_Solid(font_prompt_q,
							"DO YOU WANT TO QUIT THE GAME ??", textColor);
	SDL_Surface* prompt_option_s = TTF_RenderText_Solid(font_prompt_o,
							"PRESS Y TO QUIT AND N TO CONTINUE !!", textColor);					
	SDL_Texture* promt_qst = SDL_CreateTextureFromSurface(gRenderer,
												prompt_question_s);
	SDL_Texture* promt_opt = SDL_CreateTextureFromSurface(gRenderer,
												prompt_option_s);

	SDL_FreeSurface(prompt_question_s);
	SDL_FreeSurface(prompt_option_s);

	SDL_QueryTexture(promt_qst, NULL, NULL, &twq, &thq);
	SDL_QueryTexture(promt_opt, NULL, NULL, &two, &tho);

	renderQ.x = 15;
	renderQ.y = 50;
	renderQ.w = twq;
	renderQ.h = thq;

	renderO.x = 15;
	renderO.y = 50 + thq;
	renderO.w = two;
	renderO.h = tho;

	SDL_RenderCopy(gRenderer, promt_qst, NULL, &renderQ);
	SDL_RenderCopy(gRenderer, promt_opt, NULL, &renderO);
	SDL_RenderPresent(gRenderer);
}
