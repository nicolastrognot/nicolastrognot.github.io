/*
** sighandler.c for sighandler.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Apr 14 16:51:09 2017 Nicolas TROGNOT
** Last update Sun Apr 16 19:56:11 2017 alexis papadimitriou
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void		sighandler(const int signal,
			   int *_pid)
{
  int		status;
  static int	*pid = NULL;

  if (pid == NULL)
    pid = _pid;
  if (signal == SIGINT)
    {
      dprintf(2, "strace: Process %d detached\n", pid[0]);
      if (pid[1] == 1)
	waitpid(pid[0], &status, 0);
      ptrace(PTRACE_DETACH, pid[0], 0, 0);
      ptrace(PTRACE_CONT, pid[0], 0, 0);
      exit(0);
    }
}
