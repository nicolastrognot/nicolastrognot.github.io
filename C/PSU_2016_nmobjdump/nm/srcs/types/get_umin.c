/*
** get_umin.c for get_umin.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:12:25 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:34:23 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_umin(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  (void)shdr;
  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    c = 'u';
  return (c);
}
