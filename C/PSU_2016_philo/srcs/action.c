/*
** action.c for action.c in /home/nicolas.trognot/rendu/PSU_2016_philo
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Mar 14 15:49:56 2017 Nicolas TROGNOT
** Last update Sun Mar 19 20:42:39 2017 Nicolas TROGNOT
*/

#include "extern.h"
#include "philo.h"

int	do_eat(pthread_mutex_t *left,
	       pthread_mutex_t *right,
	       t_philo *philo,
	       int *i)
{
  int	ret;

  pthread_mutex_lock(right);
  pthread_mutex_lock(left);
  pthread_mutex_lock(philo->action_mutex);
  lphilo_take_chopstick(left);
  lphilo_take_chopstick(right);
  if (*philo->end == 1)
    ret = UNDONE;
  else
    {
      lphilo_eat();
      ret = EAT;
    }
  lphilo_release_chopstick(left);
  lphilo_release_chopstick(right);
  if ((*i = *i + 1) >= philo->nb_eat)
    *philo->end = 1;
  pthread_mutex_unlock(philo->action_mutex);
  pthread_mutex_unlock(right);
  pthread_mutex_unlock(left);
  return (ret);
}

int	do_rest(t_philo *philo)
{
  int	ret;

  pthread_mutex_lock(philo->action_mutex);
  if (*philo->end == 1)
    ret = UNDONE;
  else
    {
      lphilo_sleep();
      ret = REST;
    }
  pthread_mutex_unlock(philo->action_mutex);
  return (ret);
}

int	do_think(pthread_mutex_t *right, t_philo *philo)
{
  int	ret;

  pthread_mutex_lock(right);
  pthread_mutex_lock(philo->action_mutex);
  lphilo_take_chopstick(right);
  if (*philo->end == 1)
    ret = UNDONE;
  else
    {
      lphilo_think();
      ret = THINK;
    }
  lphilo_release_chopstick(right);
  pthread_mutex_unlock(philo->action_mutex);
  pthread_mutex_unlock(right);
  return (ret);
}
