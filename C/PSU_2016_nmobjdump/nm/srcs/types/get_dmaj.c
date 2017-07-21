/*
** get_dmaj.c for get_dmaj.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:26:42 2017 Nicolas TROGNOT
** Last update Sun Feb 26 13:58:57 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_dmaj(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS) &&
      (shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)))
    c = 'D';
  return (c);
}
