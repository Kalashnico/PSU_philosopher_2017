/*
** EPITECH PROJECT, 2018
** Philosophers
** File description:
** Array initialisers
*/

#include <stdlib.h>
#include "philosophers.h"

void init_chopsticks(t_mutex_info *chopsticks, const int nbr_philo)
{
	for (int i = 0; i < nbr_philo; i++) {
		pthread_mutex_init(&chopsticks[i].mutex, NULL);
		chopsticks[i].locked = 0;
	}
}

void init_philosopher(t_philo *philosopher, const int max_eat)
{
	philosopher->curr_state = rand() % 3;
	philosopher->curr_eat = 0;
	philosopher->max_eat = max_eat;
}
