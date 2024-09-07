#include "../headers/header.h"

/* Player Position */
SDL_Rect player;
double px = mapWidth * cellSize - 20;
double py = mapHeight * cellSize - 20;
double pdx;
double pdy;
double playerAngle = 0.0;

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
 * handle_key_input - a function to handle keyboard input
 * Description: The function updates the player's position based on key presses
 * Return: Nothing, it's a void type function
 */
void handle_key_input(void)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W]) {
        /* Move forward */
        px += cos(playerAngle) * moveSpeed;
        py += sin(playerAngle) * moveSpeed;
    }
    if (state[SDL_SCANCODE_S]) {
        /* Move backward */
        px -= cos(playerAngle) * moveSpeed;
        py -= sin(playerAngle) * moveSpeed;
    }
    if (state[SDL_SCANCODE_D]) {
        /* move perpendicular to the direction the player is facing */
        px += cos(playerAngle + M_PI / 2) * moveSpeed;
        py += sin(playerAngle + M_PI / 2) * moveSpeed;
    }
    if (state[SDL_SCANCODE_A]) {
        /* move perpendicular to the direction the player is facing */
        px += cos(playerAngle - M_PI / 2) * moveSpeed;
        py += sin(playerAngle - M_PI / 2) * moveSpeed;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        playerAngle -= rotationSpeed;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
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
    double rayAngle, rayX, rayY, stepX, stepY;

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
                draw_world(rayX, rayY, px, py, rayAngle, playerAngle, i);
            }
        }
    }
}
