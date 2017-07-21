/*
** errors.h for strace in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_strace
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Apr 11 11:59:54 2017 alexis papadimitriou
** Last update Sun Apr 16 19:39:11 2017 alexis papadimitriou
*/

#ifndef ERRORS_H_
# define ERRORS_H_
# define BIN_USGE "Usage : %s [-s] [-p <pid>|<command>]\n", av[0]

int	rerror(const char *error_msg, int value);
void	*rperror(const char *error_msg, void *value);
void	derror(const char *error_msg);

#endif /* !ERRORS_H_ */
