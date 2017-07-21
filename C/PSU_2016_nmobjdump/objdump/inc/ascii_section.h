/*
** ascii.h for ascii.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 22:59:14 2017 Nicolas TROGNOT
** Last update Sat Feb 25 23:13:58 2017 Nicolas TROGNOT
*/

#ifndef ASCII_SECTION_H_
# define ASCII_SECTION_H_
# include "struct_handler.h"

typedef struct		s_ascii
{
  unsigned int		k[4];
  unsigned char		*str;
  unsigned long		addr;
}			t_ascii;

int			print_ascii(unsigned char *str,
				    unsigned int len,
				    unsigned long addr);
int			show_sections(t_objdump *o,
				      const char *filename);

#endif /* !ASCII_SECTION_H_ */
