#include "../inc/header.h"

/**
 * Timer_IsStarted - Check if the timer has started
 * Return: 0 or 1 depend on it's started or not
 */
int Timer_IsStarted(void)
{
	return gameTime.started;
}

/**
 * Timer_IsPaused - Check if the timer is paused
 * Return: 0 or 1 depend on it's paused or not
 */
int Timer_IsPaused(void)
{
	return gameTime.paused;
}