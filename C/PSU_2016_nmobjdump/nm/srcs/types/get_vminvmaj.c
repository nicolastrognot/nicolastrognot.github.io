/*
** get_vminvmaj.c for get_vminvmaj.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:21:14 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:34:36 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_vminvmaj(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  (void)shdr;
  if ((ELF64_ST_BIND(sym->st_info) == STB_WEAK) &&
      (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT))
    {
      c = 'V';
      if (sym->st_shndx == SHN_UNDEF)
	c = 'v';
    }
  return (c);
}
