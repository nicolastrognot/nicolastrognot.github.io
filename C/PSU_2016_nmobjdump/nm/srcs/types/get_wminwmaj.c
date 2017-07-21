/*
** get_wminwmaj.c for get_wminwmaj.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:19:09 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:34:46 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_wminwmaj(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  (void)shdr;
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym->st_shndx == SHN_UNDEF)
	c = 'w';
    }
  return (c);
}
