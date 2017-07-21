/*
** extern.h for extern.h in /home/nicolas.trognot/rendu/PSU_2016_philo
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Mar 14 15:29:31 2017 Nicolas TROGNOT
** Last update Tue Mar 14 15:34:47 2017 Nicolas TROGNOT
*/

#ifndef EXTERN_H_
# define EXTERN_H_
# include <pthread.h>

int	RCFStartup(int ac, char **av);
void	RCFCleanup();
int	lphilo_eat();
int	lphilo_sleep();
int	lphilo_think();
int	lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
int	lphilo_release_chopstick(const pthread_mutex_t *mutex_id);

#endif /* !EXTERN_H_ */
