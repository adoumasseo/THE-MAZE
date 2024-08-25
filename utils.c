#include "header.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;

/**
 * init - a function that make the SDL initialization
 * 
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
            gSurface = SDL_GetWindowSurface(gWindow);
            if (gSurface == NULL)
            {
                printf("Impossible to create an Surface for the %s\n",
                                                        SDL_GetError());
                succes_status = -1;
            }
            else
            {
                SDL_FillRect(gSurface, NULL,
                            SDL_MapRGB(gSurface->format, 255, 255, 255));
                SDL_UpdateWindowSurface(gWindow);
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