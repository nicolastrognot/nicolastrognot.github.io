/*
** struct_handler.h for struct_handler.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed Feb 22 10:21:11 2017 Nicolas TROGNOT
** Last update Sat Feb 25 21:34:41 2017 Nicolas TROGNOT
*/

#ifndef STRUCT_HANDLER_H_
# define STRUCT_HANDLER_H_
# include <elf.h>

typedef struct		s_nm
{
  int			fd;
  void			*data;
  Elf64_Ehdr		*elf;
  Elf64_Shdr		*shdr;
  char			*strtab;
  char			*_strtab;
  unsigned int		sym_arr_ttl;
  Elf64_Sym		**sym_arr;
}			t_nm;

#endif /* !STRUCT_HANDLER_H_ */
