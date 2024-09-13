#include "../inc/header.h"

/**
 * random_map_path - generate a random map path
 * Description: The path is call random because we gonna use a random int in it
 * Return: The string generate
 */
char *random_map_path(void)
{
	int rand_int = random_int(), i;
	char *str = "./assets/maps/map1.txt";
	long int len = strlen(str);
	char *path = malloc(len);

	if (path == NULL)
	{
		printf("Malloc failed \n");
		return NULL;
	}
	for (i = 0; i < len; i++)
	{
		if (*(str + i) == '1')
			*(path + i) = (rand_int + '0');
		else
			*(path + i) = *(str + i);
	}
	return (path);
}