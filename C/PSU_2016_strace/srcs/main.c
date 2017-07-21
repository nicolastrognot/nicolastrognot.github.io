/*
** main.c for main.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Apr 11 11:24:22 2017 Nicolas TROGNOT
** Last update Sun Apr 16 19:43:51 2017 alexis papadimitriou
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/user.h>
#include <string.h>
#include "sighandler.h"
#include "strace.h"
#include "errors.h"
#include "quit.h"
#include "pid.h"

static int			launch(int pid,
				       void (*f)(int,
						 struct user_regs_struct *,
						 int))
{
  int				status;
  int				program_exist;
  long				rax;
  struct user_regs_struct	regs;

  program_exist = 0;
  waitpid(pid, &status, 0);
  while (check_quit(status))
    {
      program_exist = 1;
      rax = ptrace(PTRACE_PEEKUSER, pid, 8 * ORIG_RAX, NULL);
      ptrace(PTRACE_GETREGS, pid, NULL, &regs);
      if (rax >= 0 && rax < 329)
	f(rax, &regs, pid);
      ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
      waitpid(pid, &status, 0);
    }
  quit(pid, program_exist, status);
  return (0);
}

int				main(int ac, char **av)
{
  int				pid;
  int				sig[2];

  if (ac < 2)
    return (0 & dprintf(2, BIN_USGE));
  if ((pid = get_program_pid(ac, av, &sig[1])) > 0)
    {
      sig[0] = pid;
      sighandler(0, sig);
      signal(SIGINT, (void (*)(int))sighandler);
      launch(pid, (strcmp("-s", av[1]) == 0) ?
	     (string_args_display) : (basic_args_display));
    }
  else if (pid < 0)
    return (-1);
  return (0);
}
