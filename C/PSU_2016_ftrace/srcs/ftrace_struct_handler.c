/*
** ftrace_struct_handler.c for ftrace_struct_handler.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_ftrace/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May  6 13:33:00 2017 Nicolas TROGNOT
** Last update Sat May  6 13:36:26 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include "ftrace.h"

t_ftrace		*init_ftrace_struct()
{
  t_ftrace		*ftrace;

  if ((ftrace = malloc(sizeof(t_ftrace))) == NULL)
    {
      dprintf(2, "Error during ftrace allocation.\n");
      return (NULL);
    }
  ftrace->stack = NULL;
  ftrace->list = NULL;
  return (ftrace);
}
