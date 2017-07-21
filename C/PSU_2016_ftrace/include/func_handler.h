/*
** func_handler.h for func_handler.h in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_ftrace
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May  6 12:31:51 2017 Nicolas TROGNOT
** Last update Sun May  7 18:00:42 2017 Nicolas TROGNOT
*/

#ifndef FUNC_HANDLER_H_
# define FUNC_HANDLER_H_
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_func
{
  long		entry_point;
  char		*name;
  struct s_func	*next;
}		t_func;

void		add_func_to_list(t_func **, long, const char *);
t_func		*load_symtab(t_func *, Elf_Scn *, Elf64_Shdr *, Elf *);
t_func		*get_scn(t_func *, Elf *);
t_func		*load_functions(t_func *, char *);
t_func		*find_in_list(t_func *, long);

#endif /* !FUNC_HANDLER_H_ */
