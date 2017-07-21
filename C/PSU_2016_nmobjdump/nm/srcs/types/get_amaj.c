/*
** get_amaj.c for get_amaj.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:22:36 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:32:48 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_amaj(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  (void)shdr;
  if (sym->st_shndx == SHN_ABS)
    c = 'A';
  return (c);
}
