/*
** elf_handler.h for elf_handler.h in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Mon Feb 20 14:27:58 2017 Nicolas TROGNOT
** Last update Sat Feb 25 21:35:49 2017 Nicolas TROGNOT
*/

#ifndef ELF_HANDLER_H_
# define ELF_HANDLER_H_
# include <elf.h>

int		is_file_recognized(Elf64_Ehdr *elf,
				   const char *filename);
char		get_umin(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_wminwmaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_vminvmaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_umaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_amaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_cmaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_bmaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_rmaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_dmaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_tmaj(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		get_dmaj_bis(Elf64_Sym *sym, Elf64_Shdr *shdr);

#endif /* !ELF_HANDLER_H_ */
