#include "header.h"

SDL_Window *gWindow = NULL;
// SDL_Surface *gSurface = NULL;
SDL_Renderer *gRenderer = NULL;

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
        gWindow = SDL_CreateWindow("RAYCASTING TUTO", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, screenWidth,
                                    screenHeight, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Fail to create a windows %s\n", SDL_GetError());
            succes_status = -1;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Unable to create a Renderer %s\n", SDL_GetError());
                succes_status = -1;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    return (succes_status);
}

/**
 * free_close - a function to close Every thing create an alloc
 * 
 * Return: Nothing is void type
 */
void free_close(void)
{
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

/**
 * draw-close - a fct that create an viewport for the map and draw it
 * 
 * Return: Positive Integer number on succes and -1 on fail 
 */
void draw_map(void)
{
    int i, j;
    int cellSize = 8; /* Size of each cell based on the map width */
    SDL_Rect square; 

    /* Iterate through the map and draw each cell */
    for (j = 0; j < mapHeight; j++)
    {
        for (i = 0; i < mapWidth; i++)
        {
            /* Define the square's position and size */
            square.x = i * cellSize; 
            square.y = j * cellSize;
            square.w = cellSize;
            square.h = cellSize;

            /*Set the draw color based on map value*/
            if (worldMap[j][i] == 0)
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); 
            else
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

            /*Draw the rectangle */
            SDL_RenderFillRect(gRenderer, &square);

            /* Reset the color to gray to draw the line */
            SDL_SetRenderDrawColor(gRenderer, 82, 78 , 78, 255); 
            SDL_RenderDrawLineF(gRenderer, i * cellSize, 0, i * cellSize, mapHeight * cellSize - 1);
        }
        SDL_RenderDrawLine(gRenderer, 0, j * cellSize, mapWidth * cellSize - 1, j * cellSize);
    }
    /*Update the screen */
    SDL_RenderPresent(gRenderer);
}

/**
 * create_viewport - a fct that create an viewport
 * Desciption: the fct init the viewport values & set it by defautl
 * Return: Nothing it's void type function
 */
void create_viewport(void)
{
    SDL_Rect viewport;

    viewport.x = 0;
    viewport.y = 0;
    viewport.w = screenWidth / 2; /* 1/4 of the screen width */ 
    viewport.h = screenHeight / 2; /* 1/4 of the screen height */ 

    /* Set the viewport for the renderer */ 
    SDL_RenderSetViewport(gRenderer, &viewport);

    /* Clear the renderer with a background color */
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); /*Blue background*/
    SDL_RenderClear(gRenderer);
}