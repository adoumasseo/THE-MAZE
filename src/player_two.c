#include "../inc/header.h"

/**
 * set_player_pos - Set the player position to the base pos
 * Description: Basically it's set px and py to basepx and basepy
 * Which are compute based on the exit wall and are the farest possible of it
 * Return: Nothing it's void type function
 */
void set_player_pos(void)
{
	px = basepx;
	py = basepy;
	printf("(%f, %f)\n", px, py);
}