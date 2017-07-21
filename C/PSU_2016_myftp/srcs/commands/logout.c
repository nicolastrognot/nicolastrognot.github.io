/*
** logout.c for logout.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:56:53 2017 Nicolas TROGNOT
** Last update Wed May 17 11:57:06 2017 Nicolas TROGNOT
*/

#include "command_handler.h"

int	logout_quit(t_client *client, t_server *server)
{
  client->stop = 1;
  send_command(client->fd, "221 Goodbye.\r\n");
  (void)server;
  return (0);
}
