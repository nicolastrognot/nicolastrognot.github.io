/*
** main.c for main.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:33:57 2017 Nicolas TROGNOT
** Last update Wed May 17 11:35:57 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include "error.h"
#include "client_handler.h"
#include "struct_handler.h"

int			main(int ac, char **av)
{
  t_server		*myserver;
  struct sockaddr_in	s_in_c;
  socklen_t		s_s;
  int			fd;

  if (ac != 3)
    {
      dprintf(1, ERR_USAGE);
      return (0);
    }
  if ((myserver = init_server(av)) == NULL)
    return (1);
  if (chdir(av[2]) == -1)
    return (1 && dprintf(2, ERR_FILE));
  while (1)
    {
      s_s = sizeof(s_in_c);
      fd = accept(myserver->fd, (struct sockaddr *)&s_in_c, &s_s);
      fork_client(myserver, fd, &s_in_c);
      close(fd);
    }
  free_server(myserver);
  return (0);
}
