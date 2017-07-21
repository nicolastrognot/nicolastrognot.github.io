/*
** main.c for main in /home/wadel_n/Tek2/PSU_2016_philo
**
** Made by Nicolas Wadel
** Login   <wadel_n@epitech.net>
**
** Started on  Fri Mar 10 09:54:26 2017 Nicolas Wadel
** Last update Sun Mar 19 20:42:11 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include <stdio.h>
#include "error.h"
#include "extern.h"
#include "algo.h"
#include "misc.h"

void		*core(void *p)
{
  t_philo	*philo;

  philo = (t_philo *)p;
  if (philo->nb_philo % 2 == 0)
    philo->status = (philo->thread_idx % 2 == 0) ? EAT : REST;
  else
    {
      if (philo->thread_idx == (philo->nb_philo - 1))
	philo->status = REST;
      else if (philo->thread_idx == (philo->nb_philo - 2))
	philo->status = EAT;
      else
	philo->status = ((philo->thread_idx % 2 == 0) ? (THINK) : (REST));
    }
  do_algo(philo);
  pthread_mutex_lock(philo->mp);
  pthread_cond_broadcast(philo->cv);
  pthread_mutex_unlock(philo->mp);
  pthread_exit(NULL);
}

int			process_inner(t_philo *philo,
				      int *i,
				      const int nb_eat,
				      pthread_mutex_t *chopsticks)
{
  philo[i[0]].end = &i[3];
  philo[i[0]].s = &i[2];
  philo[i[0]].thread_idx = i[0];
  philo[i[0]].nb_philo = i[4];
  philo[i[0]].nb_eat = nb_eat;
  philo[i[0]].chopsticks = chopsticks;
  if ((i[1] = pthread_create(&philo[i[0]].threads, NULL, core,
			     (void *)&philo[i[0]])) != 0)
    {
      i[3] = 1;
      pthread_mutex_lock(philo[i[0]].mp);
      pthread_cond_broadcast(philo[i[0]].cv);
      pthread_mutex_unlock(philo[i[0]].mp);
      thread_create_error(i[1]);
      i[4] = i[0];
    }
  return (i[4]);
}

void			process(const int nb_philo,
				pthread_mutex_t *chopsticks,
				t_philo *philo,
				const int nb_eat)
{
  int			i[5];
  pthread_mutex_t	mp;
  pthread_mutex_t	action_mutex;
  pthread_cond_t	cv;

  mp = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  action_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  cv = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
  i[3] = 0;
  i[2] = 0;
  i[0] = -1;
  i[4] = nb_philo;
  while (++i[0] < nb_philo)
    chopsticks[i[0]] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  i[0] = -1;
  while (++i[0] < nb_philo && i[4] == nb_philo)
    {
      philo[i[0]].action_mutex = &action_mutex;
      philo[i[0]].cv = &cv;
      philo[i[0]].mp = &mp;
      i[4] = process_inner(philo, i, nb_eat, chopsticks);
    }
  i[0] = -1;
  while (++i[0] < i[4])
    pthread_join(philo[i[0]].threads, NULL);
}

void			create_threads(const int nb_philo, const int nb_eat)
{
  t_philo		*philo;
  pthread_mutex_t	*chopsticks;

  if (nb_philo < 2)
    return (not_enough_chopstick());
  if ((philo = malloc(sizeof(t_philo) * nb_philo)) == NULL ||
      (chopsticks = malloc(sizeof(pthread_mutex_t) * nb_philo)) == NULL)
    return (memory_error());
  process(nb_philo, chopsticks, philo, nb_eat);
  free(philo);
  free(chopsticks);
}

int		main(int ac, char **av)
{
  if (ac != 5 || handling_arg(ac, av) != 0)
    return (usage());
  if (my_isnbr(av[2]) != 0 || my_isnbr(av[4]) != 0)
    {
      fprintf(stderr, "Error : Argument is not a [positive] number\n");
      return (1);
    }
  RCFStartup(ac, av);
  if (av[1][1] == 'p')
    create_threads(atoi(av[2]), atoi(av[4]));
  else
    create_threads(atoi(av[4]), atoi(av[2]));
  RCFCleanup();
  return (0);
}
