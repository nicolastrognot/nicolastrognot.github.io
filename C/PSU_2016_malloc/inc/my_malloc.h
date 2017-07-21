/*
** malloc.h for malloc.h in /home/nicolas.trognot/rendu/PSU_2016_malloc/srcs/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Jan 27 13:57:03 2017 Nicolas TROGNOT
** Last update Tue Jan 31 10:59:08 2017 Côme Grellard
*/

#ifndef MALLOC_H_
# define MALLOC_H_
# include <stddef.h>
# define GET_NODE ((long)g_nodes + sizeof(t_node) + g_nodes->size)
# define GET_NODE_ELEM ((long)g_nodes->elem + sizeof(t_node) + g_nodes->size)

typedef struct __attribute__((__packed__))	s_node
{
  void						*elem;
  char						is_available;
  size_t					size;
  struct s_node					*next;
  struct s_node					*prev;
}						t_node;

void						free(void *ptr);
void						*add_node(size_t size,
							  t_node *new);
void						*malloc(size_t size);
void						*calloc(size_t nmeb,
							size_t size);
void						*realloc(void *ptr,
							size_t size);
void						show_alloc_mem(void);
void						splitter(t_node *node,
							 size_t size);
void						merger(t_node *node_to_merge);

#endif /* !MALLOC_H_ */
