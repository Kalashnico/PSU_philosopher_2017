/*
** EPITECH PROJECT, 2018
** Pḧilosophers
** File description:
** Main
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extern.h"
#include "philosophers.h"

void print_help(char *prog)
{
	printf("USAGE\n");
	printf("\t%s -p nbr_p -e nbr_e\n\n", prog);
	printf("DESCRIPTION\n");
	printf("\t-p nbr_p  number of philosophers\n");
	printf("\t-e nbr_e  maximum number times a philosopher ");
	printf("eats before exiting then program\n");
}

int check_parsing(char **av)
{
	char *p = av[1];
	char *e = av[3];

	if (strcmp(p, "-p") != 0 || strcmp(e, "-e") != 0)
		return (-1);
	if (atoi(av[2]) <= 1)
		return (-1);
	if (atoi(av[4]) <= 0)
		return (-1);
	return (0);
}

int main(int ac, char **av)
{
	int status = 0;

	srand(time(NULL));
	if (ac == 2 && strcmp(av[1], "--help") == 0)
		print_help(av[0]);
	else if (ac == 5) {
		if (check_parsing(av) == 0) {
			RCFStartup(ac, av);
			status = setup(atoi(av[2]), atoi(av[4]));
			RCFCleanup();
		}
	}
	return (status);
}