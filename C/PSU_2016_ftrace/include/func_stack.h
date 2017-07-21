/*
** func_stack.h for ftrace in /home/papadi_a/rendu/PSU_2016_ftrace
**
** Made by Alexis Papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Sat May  6 12:01:13 2017 Alexis Papadimitriou
** Last update Sun May  7 17:55:37 2017 Nicolas TROGNOT
*/

#ifndef FUNC_STACK_H_
# define FUNC_STACK_H_
# include "func_handler.h"

typedef struct		s_func_stack
{
  struct s_func_stack	*prev;
  t_func		*func;
}			t_func_stack;

t_func_stack		*push_func(t_func_stack *stack, t_func *func_called);
t_func_stack		*pop_func(t_func_stack *stack);
int			entering_function(t_func_stack **stack,
					  t_func *func_called);
void			leaving_function(t_func_stack **stack);

#endif /* !FUNC_STACK_H_ */
