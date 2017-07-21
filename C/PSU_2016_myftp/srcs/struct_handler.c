/*
** struct_handler.c for struct_handler.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:39:21 2017 Nicolas TROGNOT
** Last update Wed May 17 11:39:28 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "error.h"
#include "struct_handler.h"

t_server		*init_server(char **av)
{
  t_server		*ret;
  struct protoent	*pe;
  struct sockaddr_in	s_in;

  if ((ret = malloc(sizeof(t_server))) == NULL ||
      (ret->path = strdup(av[2])) == NULL ||
      (pe = getprotobyname("TCP")) == NULL ||
      (ret->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      dprintf(2, "%s", ERR_INIT);
      return (NULL);
    }
  ret->port = atoi(av[1]);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(ret->port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if ((bind(ret->fd, (const struct sockaddr *)&s_in, sizeof(s_in))) == -1 ||
      (listen(ret->fd, 5)) == -1)
    {
      dprintf(2, "%s", ERR_BIND);
      close (ret->fd);
      return (NULL);
    }
  return (ret);
}

void		free_server(t_server *server)
{
  close(server->fd);
  free(server->path);
  free(server);
}
