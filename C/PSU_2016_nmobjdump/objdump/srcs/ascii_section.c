/*
** ascii.c for ascii.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 22:58:45 2017 Nicolas TROGNOT
** Last update Sun Feb 26 18:35:32 2017 Nicolas TROGNOT
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "struct_handler.h"
#include "misc.h"
#include "ascii_section.h"
#include "ascii_header.h"

void			print_addr_and_hex(t_ascii *a)
{
  a->k[1] += 16;
  dprintf(1, " %0*lx ", get_addr_size(a->k[3]), a->addr);
  a->addr += 16;
  while ((a->k[2] < a->k[1]) && (a->k[2] < a->k[3]))
    {
      dprintf(1, "%02x", a->str[a->k[2]]);
      a->k[2]++;
      if ((a->k[2] % 4) == 0)
	dprintf(1, " ");
    }
  if ((a->k[2] % 16) != 0)
    {
      while ((a->k[2] % 16) != 0)
	{
	  dprintf(1, "  ");
	  a->k[2]++;
	  if ((a->k[2] % 4) == 0)
	    dprintf(1, " ");
	}
    }
  dprintf(1, " ");
}

void			init_ascii(t_ascii *a,
				   unsigned char *str,
				   unsigned int len,
				   unsigned long addr)
{
  a->k[0] = 0;
  a->k[1] = 0;
  a->k[2] = 0;
  a->k[3] = len;
  a->addr = addr;
  a->str = str;
}

int			print_ascii(unsigned char *str,
				    unsigned int len,
				    unsigned long addr)
{
  t_ascii		a;

  init_ascii(&a, str, len, addr);
  while (a.k[0] < len)
    {
      if ((a.k[0] % 16) == 0)
	print_addr_and_hex(&a);
      if ((str[a.k[0]] > 31) && (str[a.k[0]] < 127))
	write(1, &str[a.k[0]], 1);
      else
	write(1, ".", 1);
      a.k[0]++;
      if ((a.k[0] % 16) == 0)
	write(1, "\n", 1);
    }
  if ((a.k[0] % 16) != 0)
    {
      while ((a.k[0] % 16) != 0)
	{
	  write(1, " ", 1);
	  a.k[0]++;
	}
      write(1, "\n", 1);
    }
  return (0);
}

int			show_section(t_objdump *objdump,
				     int idx,
				     unsigned char *_strtab,
				     unsigned int size)
{
  size = (objdump->arch == ELFCLASS32) ? (objdump->shdr_32[idx].sh_size) :
    (objdump->shdr[idx].sh_size);
  if (size != 0)
    {
      if (objdump->arch == ELFCLASS32)
	{
	  dprintf(1, "Contents of section %s:\n",
		  &objdump->strtab[objdump->shdr_32[idx].sh_name]);
	  _strtab = (unsigned char *)(objdump->data +
				      objdump->shdr_32[idx].sh_offset);
	  print_ascii(_strtab, objdump->shdr_32[idx].sh_size,
		      objdump->shdr_32[idx].sh_addr);
	}
      else
	{
	  dprintf(1, "Contents of section %s:\n",
		  &objdump->strtab[objdump->shdr[idx].sh_name]);
	  _strtab = (unsigned char *)(objdump->data +
				      objdump->shdr[idx].sh_offset);
	  print_ascii(_strtab, objdump->shdr[idx].sh_size,
		      objdump->shdr[idx].sh_addr);
	}
    }
  return (0);
}

int		show_sections(t_objdump *o, const char *filename)
{
  unsigned int	idx;
  unsigned int	shnum;
  unsigned long	name;

  shnum = (o->arch == ELFCLASS32) ? (o->elf_32->e_shnum) :
    (o->elf->e_shnum);
  print_header(o, filename);
  idx = 0;
  while (++idx < shnum)
    {
      name = (o->arch == ELFCLASS32) ? (o->shdr_32[idx].sh_name) :
	(o->shdr[idx].sh_name);
      if (strcmp(&o->strtab[name], ".strtab") != 0 &&
	  strcmp(&o->strtab[name], ".symtab") != 0 &&
	  strcmp(&o->strtab[name], ".bss") != 0 &&
	  strcmp(&o->strtab[name], ".shstrtab") != 0 &&
	  strcmp(&o->strtab[name], ".rela.eh_frame") != 0 &&
	  strcmp(&o->strtab[name], ".rela.rodata") != 0 &&
	  strcmp(&o->strtab[name], ".rela.text") != 0)
	show_section(o, idx, NULL, 0);
    }
  return (0);
}
