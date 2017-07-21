/*
** type.c for type.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 12:03:00 2017 Nicolas TROGNOT
** Last update Wed May 17 12:05:36 2017 Nicolas TROGNOT
*/

#include "command_handler.h"

int	type_type(t_client *client, t_server *server)
{
  send_command(client->fd, "220 TYPE is now ASCII Non-print\r\n");
  (void)server;
  return (0);
}
