/*
** ftrace.h for ftrace.h in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_ftrace/includes
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May  6 12:25:21 2017 Nicolas TROGNOT
** Last update Sun May  7 22:38:28 2017 Alexis Papadimitriou
*/

#ifndef FTRACE_H_
# define FTRACE_H_
# include <libelf.h>
# include <sys/wait.h>
# include <sys/user.h>
# include "func_handler.h"
# include "func_stack.h"
# define NO_ARG "()"
# define ONE_ARG "(0x%llx)"
# define TWO_ARGS "(0x%llx, 0x%llx)"
# define THREE_ARGS "(0x%llx, 0x%llx, 0x%llx)"
# define FOUR_ARGS "(0x%llx, 0x%llx, 0x%llx, 0x%llx)"
# define FIVE_ARGS "(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx)"
# define SIX_ARGS "(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx)"

typedef union	u_call
{
  long		val;
  unsigned char	addr[sizeof(long)];
}		t_call;

typedef struct	s_sysmap
{
  char		*sysname;
  char		*arg_format;
}		t_sysmap;

typedef struct	s_ftrace
{
  t_func	*list;
  t_func_stack	*stack;
}		t_ftrace;

int		fork_failure(void);
void		trace_me(char **, pid_t);
void		syscall_promp(long, struct user_regs_struct);
void		get_trace(pid_t, t_ftrace *);
int		do_ftrace(t_ftrace *, char **);
t_ftrace	*init_ftrace_struct();

#endif /* !FTRACE_H_ */
