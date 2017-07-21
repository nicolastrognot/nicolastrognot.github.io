/*
** misc.c for misc.c in /home/nicolas.trognot/rendu/PSU_2016_malloc/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Tue Jan 31 10:24:34 2017 Nicolas TROGNOT
** Last update Fri Feb 10 13:27:26 2017 Nicolas TROGNOT
*/

#include <string.h>
#include "my_malloc.h"

void		splitter(t_node *node, size_t size)
{
  t_node	*old_prev;
  t_node	*new_next;

  node->is_available = 0;
  memset(node->elem, 0, node->size);
  if (node->size > (size + sizeof(t_node)))
    {
      old_prev = node->prev;
      new_next = (void *)((long)node + sizeof(t_node) + size);
      new_next->is_available = 1;
      new_next->size = node->size - size - sizeof(t_node);
      new_next->elem = (void *)((long)new_next + sizeof(t_node));
      new_next->prev = old_prev;
      node->prev = new_next;
      node->size = size;
    }
}

void		merger(t_node *node_to_merge)
{
  size_t	tmp_size;

  if (node_to_merge && node_to_merge->prev)
    {
      if (node_to_merge->prev->is_available == 1)
	{
	  tmp_size = node_to_merge->prev->size + sizeof(t_node);
	  if (node_to_merge->prev->prev)
	    node_to_merge->prev->prev->next = node_to_merge;
	  node_to_merge->prev = node_to_merge->prev->prev;
	  node_to_merge->size += tmp_size;
	}
    }
  if (node_to_merge && node_to_merge->next)
    {
      if (node_to_merge->next->is_available == 1)
	{
	  tmp_size = node_to_merge->size + sizeof(t_node);
	  if (node_to_merge->prev)
	    node_to_merge->prev->next = node_to_merge->next;
	  node_to_merge->next->prev = node_to_merge->prev;
	  node_to_merge->next->size += tmp_size;
	}
    }
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*tmp;
  void		*ret;

  if ((tmp = malloc(nmemb * size)) == NULL)
    return (NULL);
  ret = memset(tmp, 0, (nmemb * size));
  return (ret);
}
