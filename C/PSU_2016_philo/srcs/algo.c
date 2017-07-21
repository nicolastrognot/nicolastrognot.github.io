/*
** algo.c for algo.c in /home/nicolas.trognot/rendu/PSU_2016_philo
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Mar 14 15:48:20 2017 Nicolas TROGNOT
** Last update Sun Mar 19 20:42:54 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include "action.h"
#include "algo.h"

static int	check_s(t_philo *philo)
{
  pthread_mutex_lock(philo->mp);
  if ((*philo->s = *philo->s + 1) % philo->nb_philo == 0)
    pthread_cond_broadcast(philo->cv);
  else
    pthread_cond_wait(philo->cv, philo->mp);
  pthread_mutex_unlock(philo->mp);
  return (*philo->end);
}

void		do_algo(t_philo *philo)
{
  int		i;

  i = 0;
  while ((i < philo->nb_eat) && (*philo->end != 1) && (check_s(philo) == 0))
    {
      if (philo->status == THINK)
	philo->status = do_eat(&philo->chopsticks[philo->thread_idx],
			       &philo->chopsticks[(philo->thread_idx + 1) %
						  philo->nb_philo],
			       philo, &i);
      else if (philo->status == REST)
	philo->status = do_think(&philo->chopsticks[(philo->thread_idx + 1) %
						    philo->nb_philo],
				 philo);
      else
	philo->status = do_rest(philo);
    }
  *philo->end = 1;
}
