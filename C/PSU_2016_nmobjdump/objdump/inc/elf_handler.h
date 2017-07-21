/*
** elf_handler.h for elf_handler.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/objdump/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Mon Feb 20 14:27:58 2017 Nicolas TROGNOT
** Last update Sat Feb 25 22:04:15 2017 Nicolas TROGNOT
*/

#ifndef ELF_HANDLER_H_
# define ELF_HANDLER_H_
# include <elf.h>

int		is_file_recognized(Elf64_Ehdr *elf,
				   const char *filename);

#endif /* !ELF_HANDLER_H_ */
