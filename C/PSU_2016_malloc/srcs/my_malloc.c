/*
** malloc.c for malloc in /home/grella_c/rendu/PSU_2016_malloc
**
** Made by Côme Grellard
** Login   <grella_c@epitech.net>
**
** Started on  Thu Jan 26 11:21:30 2017 Côme Grellard
** Last update Fri Feb 10 14:53:51 2017 Côme Grellard
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "my_malloc.h"

static t_node	*g_nodes = NULL;
static size_t	ttl_gps = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/*
** Free
*/

void		free(void *ptr)
{
  t_node	*tmp;
  void		*to_break;

  pthread_mutex_lock(&mtx);
  tmp = g_nodes;
  to_break = NULL;
  while (tmp && tmp->elem != ptr)
    tmp = tmp->next;
  if ((tmp) && (tmp->elem == ptr) && ((tmp->is_available = 1) != 0))
    merger(tmp);
  while ((g_nodes) && (g_nodes->is_available == 1))
    {
      to_break = (void *)g_nodes;
      g_nodes = g_nodes->next;
      if (g_nodes != NULL)
	g_nodes->prev = NULL;
    }
  if ((to_break != NULL) &&
      ((long)to_break <= ((long)ttl_gps - getpagesize())))
    {
      brk(to_break);
      ttl_gps = (long)to_break;
    }
  pthread_mutex_unlock(&mtx);
}

/*
** Malloc
*/

void		*add_node(size_t size, t_node *new)
{
  long		sbrk_val;

  sbrk_val = (sizeof(t_node) + size) + getpagesize() -
    ((sizeof(t_node) + size) % getpagesize());
  if ((g_nodes == NULL) ||
      ((long)(GET_NODE + sizeof(t_node) + size) >= (long)ttl_gps))
    {
      if ((new = sbrk(sbrk_val)) == (void *)-1)
	return (NULL);
      new->elem = (void *)((long)new + sizeof(t_node));
      ttl_gps = (long)(new) + sbrk_val;
    }
  else
    {
      new = (void *)(GET_NODE);
      new->elem = (void *)(GET_NODE_ELEM);
    }
  new->size = size;
  new->is_available = 0;
  new->prev = NULL;
  if (g_nodes != NULL)
    g_nodes->prev = new;
  new->next = g_nodes;
  g_nodes = new;
  return (new->elem);
}

void		*malloc(size_t size)
{
  void		*ret;
  t_node	*curr;

  pthread_mutex_lock(&mtx);
  curr = g_nodes;
  while (curr != NULL)
    {
      if ((curr->is_available == 1) && (curr->size >= size))
	{
	  splitter(curr, size);
	  pthread_mutex_unlock(&mtx);
	  return (curr->elem);
	}
      curr = curr->next;
    }
  ret = add_node(size, NULL);
  pthread_mutex_unlock(&mtx);
  return (ret);
}

/*
** Realloc
*/

void		*realloc(void *ptr, size_t size)
{
  t_node	*curr;
  void		*ret;

  if (size == 0)
    free(ptr);
  if (size == 0)
    return (NULL);
  if (ptr == NULL)
    return (malloc(size));
  curr = g_nodes;
  while (curr != NULL)
    {
      if (curr->elem == ptr && curr->size >= size)
	return (curr->elem);
      else if (curr->elem == ptr)
	{
	  if ((ret = malloc(size)) == NULL)
	    return (NULL);
	  memcpy(ret, ptr, ((curr->size > size) ? size : curr->size));
	  free(curr->elem);
	  return (ret);
	}
      curr = curr->next;
    }
  return (NULL);
}

/*
** SHOW
*/

void		show_alloc_mem(void)
{
  void		*brk;
  t_node	*tmp;

  tmp = g_nodes;
  brk = sbrk(0);
  printf("break : %p\n", brk);
  while (tmp)
    {
      printf("%p - %p : %zu bytes\n", tmp->elem, tmp->elem + tmp->size,
	     tmp->size);
      tmp = tmp->next;
    }
}
