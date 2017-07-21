/*
** misc.c for misc.c in /home/nicolas.trognot/rendu/PSU_2016_philo/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Thu Mar 16 18:26:16 2017 Nicolas TROGNOT
** Last update Thu Mar 16 18:26:33 2017 Nicolas TROGNOT
*/

#include <ctype.h>

int	my_isnbr(const char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (isdigit(str[i]) == 0)
	return (1);
      ++i;
    }
  return (0);
}
