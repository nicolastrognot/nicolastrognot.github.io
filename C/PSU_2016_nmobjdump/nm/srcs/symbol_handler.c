/*
** symbol_type_handler.c for symbol_type_handler.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Thu Feb 23 08:59:49 2017 Nicolas TROGNOT
** Last update Sun Feb 26 22:31:47 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <stdlib.h>
#include "symbol_handler.h"
#include "elf_handler.h"
#include "misc.h"

char		get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		c;

  if ((c = get_umin(sym, shdr)) == 0 &&
      (c = get_wminwmaj(sym, shdr)) == 0 &&
      (c = get_vminvmaj(sym, shdr)) == 0 &&
      (c = get_umaj(sym, shdr)) == 0 &&
      (c = get_amaj(sym, shdr)) == 0 &&
      (c = get_cmaj(sym, shdr)) == 0 &&
      (c = get_bmaj(sym, shdr)) == 0 &&
      (c = get_rmaj(sym, shdr)) == 0 &&
      (c = get_dmaj(sym, shdr)) == 0 &&
      (c = get_tmaj(sym, shdr)) == 0 &&
      (c = get_dmaj_bis(sym, shdr)) == 0)
    c = '?';
  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
    c += 32;
  if (c == '?')
    c = 't';
  return (c);
}

int			is_sorted(t_nm *nm)
{
  unsigned int		i;
  Elf64_Sym		*tmp;

  i = -1;
  while (++i < nm->sym_arr_ttl)
    {
      if (i + 1 < nm->sym_arr_ttl)
	{
	  if (my_strcasecmp(&nm->_strtab[nm->sym_arr[i]->st_name],
			    &nm->_strtab[nm->sym_arr[i + 1]->st_name]) > 0)
	    {
	      tmp = nm->sym_arr[i];
	      nm->sym_arr[i] = nm->sym_arr[i + 1];
	      nm->sym_arr[i + 1] = tmp;
	      return (1);
	    }
	}
    }
  return (0);
}

int		sort_symbols(t_nm *nm)
{
  int		i;

  i = 1;
  while (i == 1)
    i = is_sorted(nm);
  return (0);
}

int			show_symbols(t_nm *nm)
{
  unsigned int		i;

  i = -1;
  while (++i < nm->sym_arr_ttl)
    {
      if (nm->sym_arr[i]->st_info != STT_FILE &&
	  nm->sym_arr[i]->st_info != STT_SECTION)
	{
	  if (nm->sym_arr[i]->st_value == 0 &&
	      get_symbol_type(nm->sym_arr[i], nm->shdr) != 'T')
	    printf("%16c %c %s\n", ' ', get_symbol_type(nm->sym_arr[i],
							nm->shdr),
		   &nm->_strtab[nm->sym_arr[i]->st_name]);
	  else
	    printf("%016lx %c %s\n", (unsigned long)nm->sym_arr[i]->st_value,
		   get_symbol_type(nm->sym_arr[i], nm->shdr),
		   &nm->_strtab[nm->sym_arr[i]->st_name]);
	}
    }
  return (0);
}

int			store_symbols(t_nm *nm)
{
  unsigned int		idx[2];
  Elf64_Sym		*_tmp;

  nm->sym_arr = NULL;
  nm->sym_arr_ttl = 0;
  idx[0] = -1;
  while (++idx[0] < nm->elf->e_shnum)
    if (nm->shdr[idx[0]].sh_type == SHT_SYMTAB)
      {
	_tmp = (Elf64_Sym *)(nm->data + nm->shdr[idx[0]].sh_offset);
	nm->sym_arr_ttl =
	  (nm->shdr[idx[0]].sh_size / nm->shdr[idx[0]].sh_entsize) - 1;
	if ((nm->sym_arr =
	     malloc(nm->sym_arr_ttl * sizeof(Elf64_Sym *))) == NULL)
	  return (1);
	idx[1] = 0;
	while (++idx[1] <
	       nm->shdr[idx[0]].sh_size / nm->shdr[idx[0]].sh_entsize)
	  nm->sym_arr[idx[1] - 1] = &_tmp[idx[1]];
      }
  sort_symbols(nm);
  show_symbols(nm);
  return (0);
}
