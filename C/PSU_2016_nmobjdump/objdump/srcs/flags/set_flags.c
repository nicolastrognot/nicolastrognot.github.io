/*
** set_types.c for set_types.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/objdump/srcs/types
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 23:24:14 2017 Nicolas TROGNOT
** Last update Sun Feb 26 18:01:18 2017 Nicolas TROGNOT
*/

#include "flags.h"

unsigned long		set_flags_maj(t_objdump *o)
{
  unsigned long		flags;
  unsigned int		idx;

  flags = 0;
  if (o->elf->e_type == ET_EXEC)
    flags += EXEC_P;
  if (o->elf->e_type == ET_DYN)
    flags += DYNAMIC;
  if (o->elf->e_type == ET_REL)
    flags += HAS_RELOC;
  idx = 0;
  while (++idx < o->elf->e_shnum)
    {
      if (o->shdr[idx].sh_type == SHT_HASH)
	flags |= D_PAGED;
      if (o->shdr[idx].sh_type == SHT_SYMTAB ||
	  o->shdr[idx].sh_type == SHT_DYNSYM)
	flags |= HAS_SYMS;
    }
  return (flags);
}

unsigned long		set_flags_min(t_objdump *o)
{
  unsigned long		flags;
  unsigned int		idx;

  flags = 0;
  if (o->elf_32->e_type == ET_EXEC)
    flags += EXEC_P;
  if (o->elf_32->e_type == ET_DYN)
    flags += DYNAMIC;
  if (o->elf_32->e_type == ET_REL)
    flags += HAS_RELOC;
  idx = 0;
  while (++idx < o->elf_32->e_shnum)
    {
      if (o->shdr_32[idx].sh_type == SHT_HASH)
	flags |= D_PAGED;
      if (o->shdr_32[idx].sh_type == SHT_SYMTAB ||
	  o->shdr_32[idx].sh_type == SHT_DYNSYM)
	flags |= HAS_SYMS;
    }
  return (flags);
}

unsigned long		set_flags(t_objdump *o)
{
  if (o->arch == ELFCLASS32)
    return (set_flags_min(o));
  return (set_flags_maj(o));
}
