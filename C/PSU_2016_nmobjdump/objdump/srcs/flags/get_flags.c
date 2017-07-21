/*
** get_flags.c for get_flags.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/objdump/srcs/flags
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 23:50:18 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:29:40 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include "flags.h"

unsigned int	display_left(unsigned int ttl,
			     unsigned long flags)
{
  if (((flags & HAS_RELOC) == HAS_RELOC) && (ttl += HAS_RELOC))
    (ttl == flags) ?
      (dprintf(1, "HAS_RELOC\n")) : (dprintf(1, "HAS_RELOC, "));
  if (((flags & EXEC_P) == EXEC_P) && (ttl += EXEC_P))
    (ttl == flags) ?
      (dprintf(1, "EXEC_P\n")) : (dprintf(1, "EXEC_P, "));
  if (((flags & HAS_LINENO) == HAS_LINENO) && (ttl += HAS_LINENO))
    (ttl == flags) ?
      (dprintf(1, "HAS_LINENO\n")) : (dprintf(1, "HAS_LINENO, "));
  return (ttl);
}

unsigned int	display_middle(unsigned int ttl,
			       unsigned long flags)
{
  if (((flags & HAS_DEBUG) == HAS_DEBUG) && (ttl += HAS_DEBUG))
    (ttl == flags) ?
      (dprintf(1, "HAS_DEBUG\n")) : (dprintf(1, "HAS_DEBUG, "));
  if (((flags & HAS_SYMS) == HAS_SYMS) && (ttl += HAS_SYMS))
    (ttl == flags) ?
      (dprintf(1, "HAS_SYMS\n")) : (dprintf(1, "HAS_SYMS, "));
  if (((flags & HAS_LOCALS) == HAS_LOCALS) && (ttl += HAS_LOCALS))
    (ttl == flags) ?
      (dprintf(1, "HAS_LOCALS\n")) : (dprintf(1, "HAS_LOCALS, "));
  return (ttl);
}

unsigned int	display_right(unsigned int ttl,
			      unsigned long flags)
{
  if (((flags & DYNAMIC) == DYNAMIC) && (ttl += DYNAMIC))
    (ttl == flags) ?
      (dprintf(1, "DYNAMIC\n")) : (dprintf(1, "DYNAMIC, "));
  if (((flags & WP_TEXT) == WP_TEXT) && (ttl += WP_TEXT))
    (ttl == flags) ?
      (dprintf(1, "WP_TEXT\n")) : (dprintf(1, "WP_TEXT, "));
  if (((flags & D_PAGED) == D_PAGED) && (ttl += D_PAGED))
    (ttl == flags) ?
      (dprintf(1, "D_PAGED\n")) : (dprintf(1, "D_PAGED, "));
  return (ttl);
}

int		print_flags(unsigned long flags)
{
  unsigned int	ttl;

  ttl = 0;
  dprintf(1, "\n");
  if (flags == 0)
    return (0);
  ttl = display_left(ttl, flags);
  ttl = display_middle(ttl, flags);
  ttl = display_right(ttl, flags);
  return (0);
}
