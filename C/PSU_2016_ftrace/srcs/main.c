/*
** main.c for main.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_ftrace/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May  6 12:26:18 2017 Nicolas TROGNOT
** Last update Sat May  6 19:39:09 2017 Nicolas TROGNOT
*/

#include "ftrace.h"

int		usage(char *str, int ret)
{
  dprintf(2, "%s <commande>\n", str);
  return (ret);
}

int		main(int ac, char **av)
{
  t_ftrace	*ftrace;

  if (ac != 2)
    return (usage(av[0], 1));
  if ((ftrace = init_ftrace_struct()) == NULL)
    return (1);
  ftrace->list = load_functions(ftrace->list, av[1]);
  do_ftrace(ftrace, av + 1);
  return (0);
}
