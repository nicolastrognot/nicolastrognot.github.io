/*
** verbose.c for verbose.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace/STRACESAVE/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Apr 15 20:03:26 2017 Nicolas TROGNOT
** Last update Sun Apr 16 19:59:02 2017 alexis papadimitriou
*/

#include <stdio.h>

int	v_int(long long unsigned int v)
{
  return (dprintf(2, "%d", (int)v));
}

int	v_uint(long long unsigned int v)
{
  return (dprintf(2, "%d", (unsigned int)v));
}

int	v_long(long long unsigned int v)
{
  return (dprintf(2, "%ld", (long)v));
}

int	v_ulong(long long unsigned int v)
{
  return (dprintf(2, "%ld", (unsigned long)v));
}

int	v_basic(long long unsigned int v)
{
  return (dprintf(2, "0x%llx", v));
}
