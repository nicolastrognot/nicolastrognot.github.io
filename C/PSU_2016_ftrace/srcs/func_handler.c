/*
** get_func_name.c for get_func_name.c  in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_ftrace/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May  6 12:26:53 2017 Nicolas TROGNOT
** Last update Sun May  7 18:01:05 2017 Nicolas TROGNOT
*/

#include "ftrace.h"
#include "func_handler.h"

void		add_func_to_list(t_func **list,
				 long entry_point, const char *str)
{
  t_func	*new;

  if (entry_point == 0 || (new = malloc(sizeof(t_func))) == NULL)
    return ;
  new->entry_point = entry_point;
  if (str)
    new->name = strdup(str);
  new->next = *list;
  *list = new;
}

t_func		*find_in_list(t_func *list, long rax)
{
  t_func	*tmp;

  tmp = list;
  while (tmp)
    {
      if (tmp->entry_point == rax)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

t_func		*load_symtab(t_func *list, Elf_Scn *scn,
			     Elf64_Shdr *shdr, Elf *e)
{
  Elf_Data	*data;
  size_t	nb_symbol;
  Elf64_Sym	*symtab;
  size_t	i;

  list = NULL;
  shdr = elf64_getshdr(scn);
  data = elf_getdata(scn, NULL);
  symtab = (Elf64_Sym *)data->d_buf;
  nb_symbol = shdr->sh_size / shdr->sh_entsize;
  i = -1;
  while (++i < nb_symbol)
    if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC ||
	ELF64_ST_TYPE(symtab[i].st_info) == STT_NOTYPE)
      add_func_to_list(&list, symtab[i].st_value,
		       elf_strptr(e, shdr->sh_link, symtab[i].st_name));
  return (list);
}

t_func		*get_scn(t_func *list, Elf *e)
{
  Elf_Scn	*scn;
  Elf64_Shdr	*shdr;

  scn = NULL;
  while ((scn = elf_nextscn(e, scn)))
    {
      if ((shdr = elf64_getshdr(scn)) == NULL)
	return (NULL);
      if (shdr->sh_type == SHT_SYMTAB)
	break;
    }
  if (!scn)
    return (NULL);
  list = load_symtab(list, scn, shdr, e);
  return (list);
}

t_func	*load_functions(t_func *list, char *file)
{
  int	fd;
  Elf	*e;

  if ((fd = open(file, O_RDONLY, 0)) == -1 ||
      elf_version(EV_CURRENT) == EV_NONE ||
      (e = elf_begin(fd, ELF_C_READ, NULL)) == NULL ||
      elf_kind(e) != ELF_K_ELF)
    return (NULL);
  list = get_scn(list, e);
  elf_end(e);
  close(fd);
  return (list);
}
