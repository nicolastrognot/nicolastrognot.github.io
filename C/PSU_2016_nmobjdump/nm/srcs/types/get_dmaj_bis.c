/*
** get_dmaj_bis.c for get_dmaj_bis.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 21:28:03 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:33:15 2017 Nicolas TROGNOT
*/

#include "elf_handler.h"

char		get_dmaj_bis(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  c = 0;
  if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  return (c);
}
