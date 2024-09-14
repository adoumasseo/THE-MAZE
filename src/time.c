#include "../inc/header.h"

/**
 * Timer_Start - start the timer
 * Return: Nothing it' void type function
 */
void Timer_Start(void)
{
	gameTime.started = 1;
	gameTime.paused = 0;
	gameTime.startTicks = SDL_GetTicks();
	gameTime.pausedTicks = 0;
}

/**
 * Timer_Stop - stop the timer
 * Return: Nothing it's void type function
 */
void Timer_Stop(void)
{
	gameTime.started = 0;
	gameTime.paused = 0;
	gameTime.startTicks = 0;
	gameTime.pausedTicks = 0;
}

/**
 * Timer_Pause - pause the time
 * Return: Nothing it's void type function
 */
void Timer_Pause(void)
{
	if (gameTime.started && !gameTime.paused)
	{
		gameTime.paused = 1;
		gameTime.pausedTicks = SDL_GetTicks() - gameTime.startTicks;
		gameTime.startTicks = 0;
	}
}

/**
 * Timer_Unpause - unpause the time
 * Return: Nothing
 */
void Timer_Unpause(void)
{
	if (gameTime.started && gameTime.paused)
	{
		gameTime.paused = 0;
		gameTime.startTicks = SDL_GetTicks() - gameTime.pausedTicks;
		gameTime.pausedTicks = 0;
	}
}

/**
 * Timer_GetTicks - Get the current ticks 
 * Return: current time i guess
 */
Uint32 Timer_GetTicks(void)
{
	Uint32 time = 0;
	if (gameTime.started)
	{
		if (gameTime.paused)
			time = gameTime.pausedTicks;
		else
			time = SDL_GetTicks() - gameTime.startTicks;
	}
	return (time);
}