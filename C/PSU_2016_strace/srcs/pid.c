/*
** pid.c for pid.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Apr 14 16:57:38 2017 Nicolas TROGNOT
** Last update Sun Apr 16 19:41:43 2017 alexis papadimitriou
*/

#include <sys/ptrace.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

int	get_program_attach_pid(int ac, char **av, int w, int *p)
{
  if (ac != (3 + w))
    {
      dprintf(2, BIN_USGE);
      return (-1);
    }
  *p = 1;
  ptrace(PTRACE_ATTACH, atoi(av[2 + w]), NULL, NULL);
  return (atoi(av[2 + w]));
}

int	get_program_pid(int ac, char **av, int *p)
{
  int	pid;

  *p = 0;
  if (strcmp("-p", av[1]) == 0)
    return (get_program_attach_pid(ac, av, 0, p));
  else if (ac > 2 && strcmp("-p", av[2]) == 0)
    return (get_program_attach_pid(ac, av, 1, p));
  if ((pid = fork()) == -1)
    return (-1);
  else if (pid == 0)
    {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      if (strcmp(av[1], "-s") != 0)
	execvp(av[1], av + 1);
      else if (ac > 2)
	execvp(av[2], av + 2);
      else
	{
	  dprintf(2, BIN_USGE);
	  return (-1);
	}
    }
  return (pid);
}
