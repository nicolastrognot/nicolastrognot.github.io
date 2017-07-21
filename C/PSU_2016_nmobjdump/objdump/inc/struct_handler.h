/*
** struct_handler.h for struct_handler.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/objdump/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed Feb 22 10:21:11 2017 Nicolas TROGNOT
** Last update Sun Feb 26 16:31:30 2017 Nicolas TROGNOT
*/

#ifndef STRUCT_HANDLER_H_
# define STRUCT_HANDLER_H_
# include <elf.h>

typedef struct		s_machine
{
  int			type;
  char			*value;
}			t_machine;

typedef struct		s_objdump
{
  char			arch;
  int			fd;
  void			*data;
  Elf64_Ehdr		*elf;
  Elf64_Shdr		*shdr;
  Elf32_Ehdr		*elf_32;
  Elf32_Shdr		*shdr_32;
  char			*strtab;
}			t_objdump;

#endif /* !STRUCT_HANDLER_H_ */
