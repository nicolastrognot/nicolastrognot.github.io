/*
** get_rmaj.c for get_rmaj.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:25:50 2017 Nicolas TROGNOT
** Last update Sun Feb 26 13:59:18 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_rmaj(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS) &&
      (shdr[sym->st_shndx].sh_flags == SHF_ALLOC))
    c = 'R';
  return (c);
}
