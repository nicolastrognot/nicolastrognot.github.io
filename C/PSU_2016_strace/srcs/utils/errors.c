/*
** errors.c for strace in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_strace
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Apr 11 12:00:41 2017 alexis papadimitriou
** Last update Sun Apr 16 19:39:01 2017 alexis papadimitriou
*/

#include <stdio.h>
#include "errors.h"

int	rerror(const char *error_msg, int value)
{
  dprintf(2, error_msg);
  return (value);
}

void	*rperror(const char *error_msg, void *value)
{
  dprintf(2, error_msg);
  return (value);
}

void	derror(const char *error_msg)
{
  dprintf(2, error_msg);
}
