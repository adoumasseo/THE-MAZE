#include "../inc/header.h"

/**
 * Timer_IsStarted - Check if the timer has started
 * Return: 0 or 1 depend on it's started or not
 */
int Timer_IsStarted(void)
{
	return (gameTime.started);
}

/**
 * Timer_IsPaused - Check if the timer is paused
 * Return: 0 or 1 depend on it's paused or not
 */
int Timer_IsPaused(void)
{
	return (gameTime.paused);
}

/**
 * check_escape_time - check if the player reach the time to lose
 * @e: The game event queue
 * Return: Nothing it's void type function
 */
void check_escape_time(SDL_Event e)
{
	if (Timer_GetTicks() >= 60000)
	{
		exit_prompt("YOU LOSE :(", "PRESS Y TO QUIT, N TO RESTART");
		handle_lose_decision(e);
	}
}