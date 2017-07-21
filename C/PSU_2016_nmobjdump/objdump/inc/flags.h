/*
** flags.h for flags.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 23:27:21 2017 Nicolas TROGNOT
** Last update Sun Feb 26 14:01:07 2017 Nicolas TROGNOT
*/

#ifndef FLAGS_H_
# define FLAGS_H_
# define BFD_NO_FLAGS	0x00
# define HAS_RELOC	0x01
# define EXEC_P		0x02
# define HAS_LINENO	0x04
# define HAS_DEBUG	0x08
# define HAS_SYMS	0x10
# define HAS_LOCALS	0x20
# define DYNAMIC	0x40
# define WP_TEXT	0x80
# define D_PAGED	0x100
# include <elf.h>
# include "struct_handler.h"

unsigned long		set_flags(t_objdump *o);
int			print_flags(unsigned long flags);

#endif /* !FLAGS_H_ */
