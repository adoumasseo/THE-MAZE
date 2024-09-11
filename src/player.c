#include "../inc/header.h"

/**
 * draw_player - a fct that draw the player
 * Desciption: the fct draw the player base on his position(lite version)
 * Return: Nothing it's void type function
 */
void draw_player(void)
{
	int lineLength = 20;

	player.x = px * draw_factor;
	player.y = py * draw_factor;
	player.w = cellSize * draw_factor;
	player.h = cellSize * draw_factor;
	SDL_RenderFillRect(gRenderer, &player);
	pdx = px + cos(playerAngle) * lineLength;
	pdy = py + sin(playerAngle) * lineLength;
}

/**
 * handle_mouse_input - handle the mouse input for rotate the plan
 *
 * Return: Nothing
 */
void handle_mouse_input(void)
{
	int mouseX, mouseY;

	SDL_SetRelativeMouseMode(SDL_TRUE);
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

/**
 * handle_key_input - a function to handle keyboard input
 * Description: The function updates the player's position based on key presses
 * Return: Nothing, it's a void type function
 */
void handle_key_input(void)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	float newPx = px, newPy = py;

	if (state[SDL_SCANCODE_W])
	{
		newPx += cos(playerAngle) * moveSpeed;/* Move forward */
		newPy += sin(playerAngle) * moveSpeed;
	}
	if (state[SDL_SCANCODE_S])
	{
		newPx -= cos(playerAngle) * moveSpeed;/* Move backward */
		newPy -= sin(playerAngle) * moveSpeed;
	}
	if (state[SDL_SCANCODE_D])
	{
		newPx += cos(playerAngle + M_PI / 2) * moveSpeed;
		newPy += sin(playerAngle + M_PI / 2) * moveSpeed;
	}
	if (state[SDL_SCANCODE_A])
	{
		newPx += cos(playerAngle - M_PI / 2) * moveSpeed;
		newPy += sin(playerAngle - M_PI / 2) * moveSpeed;
	}
	if (state[SDL_SCANCODE_LEFT])
		playerAngle -= rotationSpeed;
	if (state[SDL_SCANCODE_RIGHT])
		playerAngle += rotationSpeed;
	if (!is_wall(newPx, py))
		px = newPx;
	else
		if (!is_wall(px, newPy))
			py = newPy;
	if (!is_wall(px, newPy))
		py = newPy;
	else
		if (!is_wall(newPx, py))
			px = newPx;
}

/**
 * handle_quit - this fct will quit tell if the user press ECHAP or not
 * Return: 1 if the user press ECHAP 0 else
 */
int handle_quit(void)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
		return (1);
	return (0);
}
