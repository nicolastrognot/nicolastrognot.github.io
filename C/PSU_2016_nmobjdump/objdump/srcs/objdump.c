/*
** objdump.c for objdump.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Mon Feb 20 10:11:56 2017 Nicolas TROGNOT
** Last update Sun Feb 26 17:52:02 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include "elf_handler.h"
#include "file_handler.h"
#include "flags.h"
#include "misc.h"
#include "ascii_section.h"
#include "struct_handler.h"

int		check_size(t_objdump *nm, const char *filename)
{
  int		size_real;
  int		size_ref;

  size_real = file_size(nm->fd);
  if (nm->arch == ELFCLASS32)
    size_ref = nm->elf_32->e_shentsize * nm->elf_32->e_shnum +
      nm->elf_32->e_shoff;
  else
    size_ref = nm->elf->e_shentsize * nm->elf->e_shnum + nm->elf->e_shoff;
  if (size_real != size_ref)
    {
      printf("objdump: %s: File truncated\n", filename);
      return (1);
    }
  return (0);
}

int		do_maj(t_objdump *objdump,
		       const int ac,
		       const char *filename)
{
  objdump->arch = ELFCLASS64;
  objdump->shdr = (Elf64_Shdr *)(objdump->data + objdump->elf->e_shoff);
  if (check_size(objdump, filename) != 0)
    return (1);
  if (ac > 2)
    printf("\n%s:\n", filename);
  objdump->strtab =
    (char *)(objdump->data +
	     objdump->shdr[objdump->elf->e_shstrndx].sh_offset);
  show_sections(objdump, filename);
  return (0);
}

int		do_min(t_objdump *objdump,
		       const int ac,
		       const char *filename)
{
  objdump->arch = ELFCLASS32;
  objdump->elf_32 = (Elf32_Ehdr *)objdump->data;
  objdump->shdr_32 = (Elf32_Shdr *)(objdump->data + objdump->elf_32->e_shoff);
  if (check_size(objdump, filename) != 0)
    return (1);
  if (ac > 2)
    printf("\n%s:\n", filename);
  objdump->strtab =
    (char *)(objdump->data +
	     objdump->shdr_32[objdump->elf_32->e_shstrndx].sh_offset);
  show_sections(objdump, filename);
  return (0);
}

int		do_objdump(const int ac,
			   const char *filename)
{
  t_objdump	objdump;

  if ((objdump.fd = open_file(filename)) < 0)
    return (1);
  if ((objdump.data = mmap(NULL, file_size(objdump.fd), PROT_READ, MAP_SHARED,
			   objdump.fd, 0)) == MAP_FAILED)
    {
      printf("objdump: Warning: '%s' is not an ordinary file\n", filename);
      return (1);
    }
  objdump.elf = (Elf64_Ehdr *)objdump.data;
  if (is_file_recognized(objdump.elf, filename) != 0)
    return (1);
  if (objdump.elf->e_ident[4] == ELFCLASS64)
    {
      if ((do_maj(&objdump, ac, filename)) == 1)
	return (1);
    }
  else
    {
      if ((do_min(&objdump, ac, filename)) == 1)
	return (1);
    }
  close(objdump.fd);
  return (0);
}

int	main(int ac, char **av)
{
  int   i;
  int   ret;

  ret = 0;
  if (ac == 1)
    ret += do_objdump(ac, "a.out");
  i = 0;
  while (++i < ac)
    ret += do_objdump(ac, av[i]);
  if (ret == 0)
    return (0);
  return (1);
}
