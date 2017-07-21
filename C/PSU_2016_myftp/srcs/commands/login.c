/*
** login.c for login.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:55:57 2017 Nicolas TROGNOT
** Last update Wed May 17 11:56:35 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command_handler.h"

int	login_user(t_client *client, t_server *server)
{
  if (client->is_logged != 0)
    {
      send_command(client->fd, "530 Already logged in.\r\n");
      return (0);
    }
  free(client->username);
  client->username = strdup(client->cmd_buffer);
  send_command(client->fd, "331 Please specify the password.\r\n");
  (void)server;
  return (0);
}

int	login_pass(t_client *client, t_server *server)
{
  if (client->is_logged != 0)
    {
      send_command(client->fd, "530 Already logged in.\r\n");
      return (0);
    }
  if (client->username == NULL)
    {
      send_command(client->fd, "503 Login with USER first.\r\n");
      return (0);
    }
  if (strcasecmp(client->username, "anonymous") == 0)
    {
      client->is_logged = 1;
      chdir(server->path);
      memset(client->pwd_home, 0, 4096);
      getcwd(client->pwd_home, 4096);
      send_command(client->fd, "230 Login successful.\r\n");
      return (0);
    }
  send_command(client->fd, "530 Login incorrect.\r\n");
  (void)server;
  return (0);
}

int	login_auth(t_client *client, t_server *server)
{
  send_command(client->fd, "500 This security scheme is not implemented\r\n");
  (void)server;
  return (0);
}
