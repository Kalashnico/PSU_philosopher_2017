/*
** EPITECH PROJECT, 2018
** Philosophers
** File description:
** Philosophers
*/

#ifndef PHILOSOPHERS_H_
	#define PHILOSOPHERS_H_

#include <pthread.h>

enum e_state {
	EAT,
	SLEEP,
	THINK,
};

typedef struct s_philo {
	enum e_state curr_state;
	int curr_eat;
	int max_eat;
}	t_philo;

typedef struct s_mutex_info {
	pthread_mutex_t mutex;
	char locked;
}	t_mutex_info;

typedef struct s_args {
	t_philo *philosopher;
	t_mutex_info *left_chopstick;
	t_mutex_info *right_chopstick;
}	t_args;

/* sleep times in seconds */
	#define EAT_TIME	5
	#define THINK_TIME	3

/* philososphers.c */
int setup(int, int);

/* array_inits.c */
void init_chopsticks(t_mutex_info*, const int);
void init_philosopher(t_philo*, const int);

#endif /* !PHILOSOPHERS_H_ */
