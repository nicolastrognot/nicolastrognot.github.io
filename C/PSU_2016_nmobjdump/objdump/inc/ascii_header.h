/*
** ascii_header.h for ascii_header.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 23:33:22 2017 Nicolas TROGNOT
** Last update Sat Feb 25 23:38:19 2017 Nicolas TROGNOT
*/

#ifndef ASCII_HEADER_H_
# define ASCII_HEADER_H_
# include <stdio.h>
# include "struct_handler.h"
# include "flags.h"

int		print_header(t_objdump *o,
			     const char *filename);

#endif /* !ASCII_HEADER_H_ */
