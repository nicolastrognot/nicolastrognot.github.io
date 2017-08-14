/*
** errors.c for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Mar 28 14:00:21 2017 alexis papadimitriou
** Last update Thu Mar 30 11:00:22 2017 alexis papadimitriou
*/

#include <stdio.h>
#include "errors.h"

uint64_t	rerror(const char *error_msg, uint64_t value)
{
  dprintf(2, error_msg);
  return (value);
}

void		*rperror(const char *error_msg, void *value)
{
  dprintf(2, error_msg);
  return (value);
}

void		derror(const char *error_msg)
{
  dprintf(2, error_msg);
}
