/*
** call_handler.h for call_handler.h in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_ftrace/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May  6 14:20:39 2017 Nicolas TROGNOT
** Last update Sun May  7 17:57:52 2017 Nicolas TROGNOT
*/

#ifndef CALL_HANDLER_H_
# define CALL_HANDLER_H_
# include <sys/ptrace.h>

void	syscall_prompt(long call, struct user_regs_struct regs);
int	is_a_syscall(struct user_regs_struct regs, pid_t pid);
int	is_a_ret(struct user_regs_struct regs, pid_t pid);
long	is_a_relative_call(struct user_regs_struct regs, pid_t pid);

#endif /* !CALL_HANDLER_H_ */
