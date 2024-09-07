#include "headers/header.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

SDL_Rect viewport;
SDL_Rect player;

/*Player Position*/
double px = mapWidth * cellSize - 20;
double py = mapHeight * cellSize - 20;
double pdx;
double pdy;
double playerAngle = 0.0;
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
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    draw_player();
    
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
 * draw_player - a fct that draw the player 
 * Desciption: the fct draw the player base on his position(lite version)
 * Return: Nothing it's void type function
 */
void draw_player(void)
{
    int lineLength = 20;

    player.x = px;
    player.y = py;
    player.w = cellSize;
    player.h = cellSize;
    SDL_RenderFillRect(gRenderer, &player);

    pdx = px + cos(playerAngle) * lineLength;
    pdy = py + sin(playerAngle) * lineLength;
}

/**
 * handle_input - a function to handle keyboard input
 * Description: The function updates the player's position based on key presses
 * Return: Nothing, it's a void type function
 */
void handle_input(SDL_Event e)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W]) {
        // Move forward
        px += cos(playerAngle) * moveSpeed;
        py += sin(playerAngle) * moveSpeed;
    }

    if (state[SDL_SCANCODE_S]) {
        // Move backward
        px -= cos(playerAngle) * moveSpeed;
        py -= sin(playerAngle) * moveSpeed;
    }

    if (state[SDL_SCANCODE_A]) {
        // Move backward
        playerAngle -= rotationSpeed;
    }
    
    if (state[SDL_SCANCODE_D]) {
        // Move backward
        playerAngle += rotationSpeed;
    }
}

/**
 * cast_rays - a fct that draw the rays 
 * 
 * Return: Nothing for now
 */
void cast_rays(void)
{
    int i, hitWall, mapX, mapY;
    float rayAngle, rayX, rayY, stepX, stepY;

    for (i = 0; i < NUM_RAYS; i++)
    {
        rayAngle = playerAngle - FOV / 2 + i * (FOV / NUM_RAYS);
        rayX = px;
        rayY = py;
        stepX = cos(rayAngle);
        stepY = sin(rayAngle);

        hitWall = 0;
        while(!hitWall)
        {
            rayX += stepX;
            rayY += stepY;
            mapX = (int)rayX / cellSize;
            mapY = (int)rayY / cellSize;
            if (
                mapX >= 0 && mapX < mapWidth && mapY >= 0 &&
                mapY < mapHeight && worldMap[mapY][mapX] != 0
            )
            {
                hitWall = 1;
                SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(gRenderer, px + cellSize / 2, py + cellSize / 2, rayX, rayY);
            }
        }
    }
}