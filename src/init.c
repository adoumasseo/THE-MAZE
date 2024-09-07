#include "../inc/header.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Rect viewport;
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
	viewport.x = 0;
	viewport.y = 0;
	viewport.w = 200;
	viewport.h = 200;
	/* Set the viewport for the renderer */
	SDL_RenderSetViewport(gRenderer, &viewport);
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

	SDL_RenderSetViewport(gRenderer, NULL);
	distanceToWall = sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py));
	/* Remove eyefish effect */
	distanceToWall *= cos(ra - pa);
	/* Calculate wall height on the projection plane */
	wallHeight = (projectionPlaneDist * cellSize) / distanceToWall;
	/* Determine top and bottom of the wall slice*/
	wallTopPixel = (screenHeight / 2) - (wallHeight / 2);
	wallBottomPixel = (screenHeight / 2) + (wallHeight / 2);
	/* Set wall color (for now, let's assume gray)*/
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);
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
