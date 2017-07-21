/*
** action.h for action.h in /home/nicolas.trognot/rendu/PSU_2016_philo
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Mar 14 15:45:19 2017 Nicolas TROGNOT
** Last update Thu Mar 16 21:13:39 2017 Nicolas TROGNOT
*/

#ifndef ACTION_H_
# define ACTION_H_
# include "philo.h"

int	do_eat(pthread_mutex_t *left, pthread_mutex_t *right,
	       t_philo *philo, int *i);
int	do_think(pthread_mutex_t *right, t_philo *philo);
int	do_rest(t_philo *philo);

#endif /* !ACTION_H_ */
