/*
** error.h for error.h in /home/nicolas.trognot/rendu/PSU_2016_philo/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Mar 14 15:36:36 2017 Nicolas TROGNOT
** Last update Tue Mar 14 15:44:04 2017 Nicolas TROGNOT
*/

#ifndef ERROR_H_
# define ERROR_H_

int	handling_arg(int ac, char **av);
int	usage(void);
void	not_enough_chopstick(void);
void	thread_create_error(const int error);
void	memory_error(void);

#endif /* !ERROR_H_ */
