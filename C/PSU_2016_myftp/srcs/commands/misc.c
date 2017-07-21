/*
** misc.c for misc.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:57:15 2017 Nicolas TROGNOT
** Last update Wed May 17 11:57:35 2017 Nicolas TROGNOT
*/

#include "command_handler.h"

int	misc_noop(t_client *client, t_server *server)
{
  send_command(client->fd, "200 NOOP ok.\r\n");
  (void)server;
  return (0);
}

int	misc_syst(t_client *client, t_server *server)
{
  send_command(client->fd, "215 UNIX Type: L8\r\n");
  (void)server;
  return (0);
}
