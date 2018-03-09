/*
** EPITECH PROJECT, 2018
** Philosophers
** File description:
** Philosophers
*/

#include <unistd.h>
#include <stdlib.h>
#include "extern.h"
#include "philosophers.h"

void philo_eat(t_philo *philo,
		t_mutex_info *left_chopstick,
		t_mutex_info *right_chopstick)
{
	if (left_chopstick->locked == 0 && right_chopstick->locked == 0) {
		pthread_mutex_lock(&left_chopstick->mutex);
		if (pthread_mutex_trylock(&right_chopstick->mutex) != 0) {
			pthread_mutex_unlock(&left_chopstick->mutex);
			return;
		}
		left_chopstick->locked = 1;
		right_chopstick->locked = 1;
		lphilo_take_chopstick(&left_chopstick->mutex);
		lphilo_take_chopstick(&right_chopstick->mutex);
		lphilo_eat();
		pthread_mutex_unlock(&right_chopstick->mutex);
		pthread_mutex_unlock(&left_chopstick->mutex);
		sleep(EAT_TIME);
		lphilo_release_chopstick(&right_chopstick->mutex);
		lphilo_release_chopstick(&left_chopstick->mutex);
		philo->curr_eat++;
		philo->curr_state = SLEEP;
		left_chopstick->locked = 0;
		right_chopstick->locked = 0;
	}
}

void philo_sleep(t_philo *philo)
{
	lphilo_sleep();
	philo->curr_state = THINK;
}

void philo_think(t_philo *philo,
		t_mutex_info *left_chopstick,
		t_mutex_info *right_chopstick)
{
	if (left_chopstick->locked == 0) {
		pthread_mutex_lock(&left_chopstick->mutex);
		left_chopstick->locked = 1;
		lphilo_take_chopstick(&left_chopstick->mutex);
		lphilo_think();
		pthread_mutex_unlock(&left_chopstick->mutex);
		sleep(THINK_TIME);
		lphilo_release_chopstick(&left_chopstick->mutex);
		philo->curr_state = EAT;
		left_chopstick->locked = 0;
	} else if (right_chopstick->locked == 0) {
		pthread_mutex_lock(&right_chopstick->mutex);
		right_chopstick->locked = 1;
		lphilo_take_chopstick(&right_chopstick->mutex);
		lphilo_think();
		pthread_mutex_unlock(&right_chopstick->mutex);
		sleep(THINK_TIME);
		lphilo_release_chopstick(&right_chopstick->mutex);
		philo->curr_state = EAT;
		right_chopstick->locked = 0;
	}
}

void *thread_entry(void *arguments)
{
	t_args *args = arguments;
	t_philo *philo = args->philosopher;
	t_mutex_info *left_chopstick = args->left_chopstick;
	t_mutex_info *right_chopstick = args->right_chopstick;

	while (philo->curr_eat != philo->max_eat) {
		if (philo->curr_state == EAT)
			philo_eat(philo, left_chopstick, right_chopstick);
		else if (philo->curr_state == SLEEP)
			philo_sleep(philo);
		else
			philo_think(philo, left_chopstick, right_chopstick);
	}
	return (0);
}

int setup(const int nbr_philo, const int max_eat)
{
	t_mutex_info chopstick[nbr_philo];
	t_philo philosopher[nbr_philo];
	pthread_t thread[nbr_philo];
	t_args args[nbr_philo];

	init_chopsticks(chopstick, nbr_philo);
	for (int i = 0; i < nbr_philo; i++) {
		init_philosopher(&philosopher[i], max_eat);
		args[i].philosopher = &philosopher[i];
		args[i].left_chopstick = &chopstick[i];
		if (i != nbr_philo - 1)
			args[i].right_chopstick = &chopstick[i + 1];
		else
			args[i].right_chopstick = &chopstick[0];
		if (pthread_create(&thread[i], 0, thread_entry, &args[i]) != 0)
			return (84);
	}
	for (int i = 0; i < nbr_philo; i++)
		if (pthread_join(thread[i], NULL) != 0)
			return (84);
	return (0);
}
