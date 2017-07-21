/*
** client_handler.c for client_handler.h in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:22:17 2017 Nicolas TROGNOT
** Last update Sat May 20 12:37:27 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "error.h"
#include "client_handler.h"
#include "command_handler.h"

void		launch_client(t_client *c,
			      t_server *s)
{
  size_t	len;
  ssize_t	read;

  len = 0;
  if ((c->pid = fork()) == 0)
    {
      send_command(c->fd, "220 Welcome to the myftp project of Trogno_n\r\n");
      while (c->stop == 0 &&
	     (read = getline(&c->buffer, &len, c->file)) != -1)
	{
	  c->buffer[strlen(c->buffer) - 1] = '\0';
	  if (c->buffer[strlen(c->buffer) - 1] == '\r')
	    c->buffer[strlen(c->buffer) - 1] = '\0';
	  detect_command(c, s);
	  free(c->buffer);
	  c->buffer = NULL;
	}
      free(c->username);
      free(c->ip_server);
      close(c->fd);
      close(s->fd);
      exit(0);
    }
  else if (c->pid != -1)
    close(c->fd);
}

int		fork_client(t_server *server, int fd,
			    struct sockaddr_in *s_in_c)
{
  t_client	client;

  if (fd == -1)
    {
      dprintf(2, "%s", ERR_FDCLIENT);
      return (1);
    }
  client.is_logged = 0;
  client.fd = fd;
  client.file = fdopen(fd, "r");
  client.data_fd = -1;
  client.stop = 0;
  client.ip_server = strdup(inet_ntoa(s_in_c->sin_addr));
  client.username = NULL;
  client.buffer = NULL;
  launch_client(&client, server);
  return (0);
}
