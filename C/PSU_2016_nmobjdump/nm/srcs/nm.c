/*
** nm.c for nm.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Mon Feb 20 10:11:38 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:31:20 2017 Nicolas TROGNOT
*/

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include "file_handler.h"
#include "elf_handler.h"
#include "struct_handler.h"
#include "symbol_handler.h"
#include "misc.h"

char		*get_strtab(t_nm *nm, const char *filename)
{
  int		i;

  i = -1;
  while (++i < nm->elf->e_shnum)
    if (strcmp(&nm->strtab[nm->shdr[i].sh_name], ".strtab") == 0)
      return (nm->data + nm->shdr[i].sh_offset);
  printf("nm: %s: no symbols\n", filename);
  return (NULL);
}

int		check_size(t_nm *nm, const char *filename)
{
  int		size_real;
  int		size_ref;

  size_real = file_size(nm->fd);
  size_ref = nm->elf->e_shentsize * nm->elf->e_shnum + nm->elf->e_shoff;
  if (size_real != size_ref)
    {
      printf("nm: %s: File truncated\n", filename);
      return (1);
    }
  return (0);
}

int		do_nm(const int ac,
		      const char *filename)
{
  t_nm		my_nm;

  if ((my_nm.fd = open_file(filename)) < 0)
    return (1);
  if ((my_nm.data = mmap(NULL, file_size(my_nm.fd), PROT_READ, MAP_SHARED,
			 my_nm.fd, 0)) == MAP_FAILED)
    {
      printf("nm: Warning: '%s' is not an ordinary file\n", filename);
      return (1);
    }
  my_nm.elf = (Elf64_Ehdr *)my_nm.data;
  if (is_file_recognized(my_nm.elf, filename) != 0 ||
      check_size(&my_nm, filename) != 0)
    return (1);
  my_nm.shdr = (Elf64_Shdr *)(my_nm.data + my_nm.elf->e_shoff);
  if (ac > 2)
    printf("\n%s:\n", filename);
  my_nm.strtab = (char *)(my_nm.data +
			  my_nm.shdr[my_nm.elf->e_shstrndx].sh_offset);
  if ((my_nm._strtab = get_strtab(&my_nm,
				  filename)) == NULL)
    return (0);
  store_symbols(&my_nm);
  close(my_nm.fd);
  return (0);
}

int	main(int ac, char **av)
{
  int	i;
  int	ret;

  ret = 0;
  if (ac == 1)
    ret += do_nm(ac, "a.out");
  i = 0;
  while (++i < ac)
    ret += do_nm(ac, av[i]);
  return (ret);
}
