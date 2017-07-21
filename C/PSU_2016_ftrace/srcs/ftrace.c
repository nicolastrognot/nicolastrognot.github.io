/*
** ftrace.c for ftrace.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_ftrace/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May  6 14:07:12 2017 Nicolas TROGNOT
** Last update Sun May  7 22:59:25 2017 Nicolas TROGNOT
*/

#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "ftrace.h"
#include "call_handler.h"

void	trace_me(char **exec, pid_t pid)
{
  ptrace(PT_TRACE_ME, pid, NULL, NULL);
  execvp(exec[0], exec);
}

int				get_trace_in(int output_next,
					     struct user_regs_struct regs,
					     pid_t pid,
					     t_ftrace *ftrace)
{
  if (output_next == 1)
    {
      if (find_in_list(ftrace->list, regs.rip) != NULL)
	entering_function(&ftrace->stack,
			  find_in_list(ftrace->list, regs.rip));
      output_next = 0;
    }
  else if (output_next == 2)
    {
      dprintf(1, " = 0x%llx\n", regs.rax);
      output_next = 0;
    }
  if (is_a_syscall(regs, pid))
    {
      syscall_prompt(regs.rax, regs);
      output_next = 2;
    }
  return (output_next);
}

void				get_trace(pid_t pid, t_ftrace *ftrace)
{
  struct user_regs_struct	regs;
  int				status;
  int				output_next;

  output_next = 0;
  while (1)
    {
      ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
      wait4(pid, &status, 0, NULL);
      ptrace(PTRACE_GETREGS, pid, NULL, &regs);
      output_next = get_trace_in(output_next, regs, pid, ftrace);
      if (is_a_relative_call(regs, pid) != -1)
	output_next = 1;
      if (is_a_ret(regs, pid))
	leaving_function(&ftrace->stack);
      if (WIFEXITED(status))
	break ;
    }
}

int		do_ftrace(t_ftrace *ftrace, char **exec)
{
  pid_t		pid;

  pid = fork();
  if (pid == 0)
    trace_me(exec, pid);
  else if (pid == -1)
    {
      dprintf(2, "error: fork() failed\n");
      return (1);
    }
  else if (pid != 0)
    get_trace(pid, ftrace);
  return (0);
}
