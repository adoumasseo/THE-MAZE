#include "../inc/header.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Rect ath_viewport;
int screenWidth;
int screenHeight;


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
	game_viewport.w = screenWidth -200;
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
	SDL_Quit();
}

/**
 * draw_world - this draw the world
 * @rx: the ray end x coordinates
 * @ry: the ray en y coordinates
 * @px: the player x coordinates
 * @py: the player y coordinates
 * @ra: the ray angle
 * @pa: the player direction angle
 * @index: the current index in the cast_rays loop
 */
void draw_world(double rx, double ry, double px,
		double py, double ra, double pa, int index)
{
	int wallTopPixel, wallBottomPixel;
	float distanceToWall, wallHeight;
	const double projectionPlaneDist = (screenWidth / 2) / tan(FOV / 2);
	Uint32 drawColor;
	Uint8 r, g, b, a;
	
	distanceToWall = sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py));
	distanceToWall *= cos(ra - pa); /*eyefish effect */
	wallHeight = (projectionPlaneDist * cellSize) / distanceToWall;
	wallTopPixel = (screenHeight / 2) - (wallHeight / 2);
	wallBottomPixel = (screenHeight / 2) + (wallHeight / 2);
	drawColor = handle_light_effect((100 << 24) | (100 << 16) | (100 << 8) | 255, distanceToWall);
	r = (drawColor >> 24) & 0xFF;
	g = (drawColor >> 16) & 0xFF;
	b = (drawColor >> 8) & 0xFF;
	a = drawColor & 0xFF;
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
	/* Draw the vertical line representing the wall slice */
	SDL_RenderDrawLine(gRenderer, index, wallTopPixel, index, wallBottomPixel);
}

/**
 * handle_mouse_input - handle the mouse input for rotate the plan
 *
 * Return: Nothing
 */
void handle_mouse_input(void)
{
	int mouseX, mouseY;

	SDL_GetRelativeMouseState(&mouseX, &mouseY);
	if (mouseX != 0)
	{
		/* angle based on horizontal mouse movement (mouseX) */
		playerAngle += mouseX * 0.005;
	}
	if (playerAngle < 0)
	{
		playerAngle += 2 * M_PI;
	}
	if (playerAngle > 2 * M_PI)
	{
		playerAngle -= 2 * M_PI;
	}
}
