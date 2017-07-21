/*
** get_umaj.c for get_umaj.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:21:51 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:34:02 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_umaj(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  (void)shdr;
  if (sym->st_shndx == SHN_UNDEF)
    c = 'U';
  return (c);
}
