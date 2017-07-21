/*
** elf_handler.c for elf_handler.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Mon Feb 20 14:24:48 2017 Nicolas TROGNOT
** Last update Sat Feb 25 21:36:26 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <elf.h>

int	is_file_recognized(Elf64_Ehdr *elf,
			   const char *filename)
{
  if ((elf->e_ident[0] != ELFMAG0) || (elf->e_ident[1] != ELFMAG1) ||
      (elf->e_ident[2] != ELFMAG2) || (elf->e_ident[3] != ELFMAG3))
    {
      printf("nm: %s: File format not recognized\n", filename);
      return (1);
    }
  return (0);
}
