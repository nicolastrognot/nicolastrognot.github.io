/*
** error.c for error.c in /home/nicolas.trognot/rendu/PSU_2016_philo/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Mar 14 15:36:23 2017 Nicolas TROGNOT
** Last update Sun Mar 19 20:38:09 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <string.h>

int	handling_arg(int ac, char **av)
{
  int	i;
  int	flag_p;
  int	flag_e;

  i = 0;
  flag_p = 0;
  flag_e = 0;
  while (++i < ac)
    {
      if (strcmp(av[i], "-p") == 0)
	{
	  if (flag_p == 0)
	    flag_p = 1;
	  else
	    return (1);
	}
      else if (strcmp(av[i], "-e") == 0)
	{
	  if (flag_e == 0)
	    flag_e = 1;
	  else
	    return (1);
	}
    }
  return (!(flag_p == 1 && flag_e == 1));
}

int	usage(void)
{
  fprintf(stderr, "Usage : ./philo -p [number] -e [number]\n");
  return (1);
}

void	not_enough_chopstick(void)
{
  fprintf(stderr, "Error : Not enought shopstick to eat : Aborting !\n");
}

void	thread_create_error(const int error)
{
  fprintf(stderr, "Error : %s\n", strerror(error));
}

void	memory_error(void)
{
  fprintf(stderr, "Error : Malloc failed (Not enought memory)\n");
}
