/*
** philo.h for philo.h in /home/nicolas.trognot/rendu/PSU_2016_philo/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Mar 14 15:33:56 2017 Nicolas TROGNOT
** Last update Thu Mar 16 21:35:40 2017 Nicolas TROGNOT
*/

#ifndef PHILO_H_
# define PHILO_H_
# include <pthread.h>
# define EAT (2)
# define THINK (1)
# define REST (0)
# define UNDONE (-1)

typedef struct		s_philo
{
  pthread_mutex_t	*chopsticks;
  pthread_t		threads;
  int			thread_idx;
  int			nb_philo;
  int			nb_eat;
  int			status;
  int			*s;
  int			*end;
  pthread_mutex_t	*mp;
  pthread_mutex_t	*action_mutex;
  pthread_cond_t	*cv;
}			t_philo;

#endif /* !PHILO_H_ */
