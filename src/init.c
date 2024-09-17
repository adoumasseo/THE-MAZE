#include "../inc/header.h"

/**
 * init - a function that make the SDL initialization
 * Description: Create gWindow, gRenderer, gSurface
 * Return: Positive number on succes and -1 if fail
 */
int init(void)
{
	int succes_status = 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1)
	{
		printf("Fail to init: %s\n, %s\n", SDL_GetError(), TTF_GetError());
		succes_status = -1;
	}
	else
	{
		getScreenBound();
		if (!init_font() || init_music())
			succes_status = -1;
		gWindow = SDL_CreateWindow("RAYCASTING TUTO",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
		}
	}
	return (succes_status);
}

/**
 * init_font - init the variable font value
 * Return: 0 if fail 1 else
 */
int init_font(void)
{
	font_prompt_q = TTF_OpenFont("./assets/fonts/Montserrat-Black.ttf", 30);
	font_prompt_o = TTF_OpenFont("./assets/fonts/Montserrat-Medium.ttf", 20);
	if (font_prompt_o == NULL || font_prompt_q == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return (0);
	}
	return (1);
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
	Mix_FreeMusic(bg_music);
	Mix_CloseAudio();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	/*free_texture_of_upng();*/
	TTF_Quit();
	SDL_Quit();
}

/**
 * init_music - This function is supposed to init the SDL2 music lib
 * Return: 1 on succes 0 else
 */
int init_music(void)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer can init!(init_music): %s\n", Mix_GetError());
		return (0);
	}
	else
	{
		bg_music = Mix_LoadMUS("backgound.wav");
		if (!bg_music)
		{
			printf("music can be load %s\n", Mix_GetError());
			return (0);
		}
	}
	return (1);
}