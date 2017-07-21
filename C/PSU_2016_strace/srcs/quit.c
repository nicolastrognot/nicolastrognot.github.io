/*
** quit.c for quit.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Apr 14 16:41:21 2017 Nicolas TROGNOT
** Last update Sun Apr 16 17:40:47 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

static const char	*g_kill[] =
  {
    "SIGHUP",
    "SIGINT",
    "SIGQUIT",
    "SIGILL",
    "SIGTRAP",
    "SIGABRT",
    "SIGBUS",
    "SIGFPE",
    "SIGKILL",
    "SIGUSR1",
    "SIGSEGV",
    "SIGUSR2",
    "SIGPIPE",
    "SIGALRM",
    "SIGTERM",
    "SIGSTKFLT",
    "SIGCHLD",
    "SIGCONT",
    "SIGSTOP",
    "SIGTSTP",
    "SIGTTIN",
    "SIGTTOU",
    "SIGURG",
    "SIGXCPU",
    "SIGXFSZ",
    "SIGVTALRM",
    "SIGPROF",
    "SIGWINCH",
    "SIGIO",
    "SIGPWR",
    "SIGSYS",
    "SIGRTMIN"
  };

int			quit(const int pid,
			     const int program_exist,
			     const int status)
{
  int			nb;

  if (program_exist)
    {
      if (WEXITSTATUS(status) > 0 && WEXITSTATUS(status) <= 34)
	dprintf(2, "+++ killed by %s +++\n",
		g_kill[WEXITSTATUS(status) - 1]);
      else
	{
	  nb = dprintf(2, "exit_group(0x%x)", WEXITSTATUS(status));
	  while (++nb < 40)
	    dprintf(2, " ");
	  dprintf(2, " = ?\n");
	  dprintf(2, "+++ exited with 0x%x +++\n", WEXITSTATUS(status));
	}
    }
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  return (0);
}

int			check_quit(const int status)
{
  return (WIFSTOPPED(status) && ((WSTOPSIG(status) == SIGTRAP ||
				  WSTOPSIG(status) == SIGSTOP)));
}
