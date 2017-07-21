/*
** symbol_type_handler.h for symbol_type_handler.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Thu Feb 23 09:02:09 2017 Nicolas TROGNOT
** Last update Thu Feb 23 09:44:03 2017 Nicolas TROGNOT
*/

#ifndef SYMBOL_TYPE_HANDLER_H_
# define SYMBOL_TYPE_HANDLER_H_
# include <elf.h>
# include "struct_handler.h"

char		get_symbol_type(Elf64_Sym *sym,
				Elf64_Shdr *shdr);
int		is_sorted(t_nm *nm);
int		sort_symbols(t_nm *nm);
int		show_symbols(t_nm *nm);
int		store_symbols(t_nm *nm);

#endif /* !SYMBOL_TYPE_HANDLER_H_ */
