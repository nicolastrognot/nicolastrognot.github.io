/*
** strace.h for strace in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_strace
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Wed Apr 12 13:34:17 2017 alexis papadimitriou
** Last update Sun Apr 16 17:29:51 2017 Nicolas TROGNOT
*/

#ifndef STRACE_H_
# define STRACE_H_
# define INT 1
# define UINT 2
# define LONG 3
# define ULONG 4
# define STRING 5
# define VARGS 6
# define VOID 7
# define PTR 8
# define BASIC 9
# include <sys/reg.h>

typedef struct	s_verbose
{
  const int	type;
  int		(*display)(long long unsigned int, int);
}		t_verbose;

typedef struct	s_syscall
{
  const char	*name;
  const int	nb_args;
  const int	ret_type;
  const int	args_type[6];
}		t_syscall;

void		string_args_display(int offset, struct user_regs_struct *regs,
				    int pid);
void		basic_args_display(int offset, struct user_regs_struct *regs,
				   int pid);

#endif /* !STRACE_H_ */
