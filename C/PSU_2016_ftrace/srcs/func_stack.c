/*
** func_stack.c for ftrace in /home/papadi_a/rendu/PSU_2016_ftrace
**
** Made by Alexis Papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Sat May  6 12:11:39 2017 Alexis Papadimitriou
** Last update Sun May  7 17:59:02 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include <stdio.h>
#include "ftrace.h"
#include "func_stack.h"

t_func_stack		*push_func(t_func_stack *stack, t_func *func_called)
{
  t_func_stack		*new;

  if ((new = malloc(sizeof(t_func_stack))) == NULL)
    return (NULL);
  new->prev = stack;
  new->func = func_called;
  return (new);
}

t_func_stack		*pop_func(t_func_stack *stack)
{
  t_func_stack		*popped_stack_ptr;

  if (stack == NULL)
    return (NULL);
  popped_stack_ptr = stack->prev;
  free(stack);
  return (popped_stack_ptr);
}

int			entering_function(t_func_stack **stack,
					  t_func *func_called)
{
  if (func_called->name == NULL)
    dprintf(1, "Entering function at %p\n", (void *)func_called->entry_point);
  else
    dprintf(1, "Entering function %s at %p\n",
	    func_called->name, (void *)func_called->entry_point);
  *stack = push_func(*stack, func_called);
  return (0);
}

void			leaving_function(t_func_stack **stack)
{
  t_func		*func;

  if (*stack == NULL)
    return ;
  func = (*stack)->func;
  if (func->name == NULL)
    dprintf(1, "Leaving function at %p\n", (void *)func->entry_point);
  else
    dprintf(1, "Leaving function %s at %p\n",
	    func->name, (void *)func->entry_point);
  *stack = pop_func(*stack);
}
