#include "../inc/header.h"

/**
 * init - a function that make the SDL initialization
 * Description: Create gWindow, gRenderer, gSurface
 * Return: Positive number on succes and -1 if fail
 */
int init(void)
{
	int succes_status = 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Fail to init: %s\n", SDL_GetError());
		succes_status = -1;
	}
	else
	{
		getScreenBound();
		gWindow = SDL_CreateWindow("RAYCASTING TUTO", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, screenWidth,
					screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	}
	if (gWindow == NULL)
	{
		printf("Fail to create a windows %s\n", SDL_GetError());
		succes_status = -1;
	}
	else
	{
		SDL_MaximizeWindow(gWindow);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL)
		{
			printf("Unable to create a Renderer %s\n", SDL_GetError());
			succes_status = -1;
		}
		else
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);
			SDL_RenderPresent(gRenderer);
			/*if (!load_texture_with_upng())
			{
				printf("Error loading IMG \n");
				succes_status = -1;
			}*/
		}
	}
	return (succes_status);
}

/**
 * create_viewport - a fct that create an viewport
 * Desciption: the fct init the viewport values & set it by defautl
 * Return: Nothing it's void type function
 */
void create_viewport(void)
{
	/* Viewport for ATH*/
	ath_viewport.x = 0;
	ath_viewport.y = 0;
	ath_viewport.w = 200;
	ath_viewport.h = screenHeight;
	/* Viewport for Game */
	game_viewport.x = 200;
	game_viewport.y = 0;
	game_viewport.w = screenWidth - 200;
	game_viewport.h = screenHeight;
	/* Set the viewport for the renderer */
	SDL_RenderSetViewport(gRenderer, &ath_viewport);
	/* Clear the renderer with a background color */
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); /*Black background*/
	SDL_RenderClear(gRenderer);
}

/**
 * free_close - a function to close Every thing create an alloc
 *
 * Return: Nothing is void type
 */
void free_close(void)
{
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	/*free_texture_of_upng();*/
	SDL_Quit();
}
