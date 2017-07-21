/*
** ascii_header.c for ascii_header.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/objdump/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 23:32:55 2017 Nicolas TROGNOT
** Last update Sun Feb 26 18:13:38 2017 Nicolas TROGNOT
*/

#include "ascii_header.h"

static const t_machine		machines[10] =
  {
    {EM_386, "i386"},
    {EM_68K, "m68k"},
    {EM_860, "i860"},
    {EM_88K, "m88k"},
    {EM_PPC, "ppc"},
    {EM_PPC64, "ppc64"},
    {EM_SH, "sh"},
    {EM_SPARCV9, "sparcv9"},
    {EM_X86_64, "x86-64"},
    {EM_NONE, "unknown"}
  };

char		*get_machine(int m)
{
  int		i;

  i = 0;
  while (machines[i].type != 0)
    {
      if (machines[i].type == m)
	return (machines[i].value);
      i++;
    }
  return ("none");
}

int			print_header_maj(t_objdump *o,
					 const char *filename)
{
  unsigned long		flags;

  flags = set_flags(o);
  dprintf(1, "\n%s:     file format ", filename);
  if (o->elf->e_ident[4] == ELFCLASS32)
    dprintf(1,"elf32-");
  else
    dprintf(1,"elf64-");
  dprintf(1, "%s", get_machine(o->elf->e_machine));
  dprintf(1, "\narchitecture: %s", ((o->elf->e_flags == 0) ?
				    ("i386:") : ("")));
  dprintf(1, "%s", get_machine(o->elf->e_machine));
  dprintf(1, ", flags 0x%08lx:", flags);
  print_flags(flags);
  dprintf(1, "start address 0x%016lx", o->elf->e_entry);
  dprintf(1, "\n\n");
  return (0);
}

int			print_header_min(t_objdump *o,
					 const char *filename)
{
  unsigned long		flags;

  flags = set_flags(o);
  dprintf(1, "\n%s:     file format ", filename);
  if (o->elf_32->e_ident[4] == ELFCLASS32)
    dprintf(1,"elf32-");
  else
    dprintf(1,"elf64-");
  dprintf(1, "%s", get_machine(o->elf_32->e_machine));
  dprintf(1, "\narchitecture: ");
  dprintf(1, "%s", get_machine(o->elf_32->e_machine));
  dprintf(1, ", flags 0x%08lx:", flags);
  print_flags(flags);
  dprintf(1, "start address 0x%08lx", (unsigned long)o->elf_32->e_entry);
  dprintf(1, "\n\n");
  return (0);
}

int			print_header(t_objdump *o,
				     const char *filename)
{
  if (o->arch == ELFCLASS32)
    return (print_header_min(o, filename));
  else
    return (print_header_maj(o, filename));
}
