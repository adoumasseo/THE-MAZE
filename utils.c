#include "header.h"

SDL_Window *gWindow = NULL;
// SDL_Surface *gSurface = NULL;
SDL_Renderer *gRenderer = NULL;

/**
 * init - a function that make the SDL initialization
 * Description: Create gWindow, gRenderer, gSurface
 * Return: Positive number on succes and -1 if fail
 */
int init()
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
void free_close()
{
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}
