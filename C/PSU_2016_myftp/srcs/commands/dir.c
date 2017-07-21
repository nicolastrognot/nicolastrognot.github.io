/*
** dir.c for dir.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:54:14 2017 Nicolas TROGNOT
** Last update Sat May 20 22:00:32 2017 Nicolas TROGNOT
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "command_handler.h"

int	dir_cwd(t_client *client, t_server *server)
{
  char	pwd[4096];
  char	buffer[4096];

  memset(pwd, 0, 4096);
  memcpy(pwd, client->cmd_buffer, strlen(client->cmd_buffer));
  if (client->cmd_buffer[0] == '/')
    {
      memset(pwd, 0, 4096);
      memcpy(pwd, client->pwd_home, strlen(client->pwd_home));
      strcat(pwd, client->cmd_buffer);
    }
  if (chdir(pwd) == -1)
    send_command(client->fd, "550 Failed to change directory.\r\n");
  else
    {
      if (strncmp(client->pwd_home, getcwd(buffer, 4096),
		  strlen(client->pwd_home)) != 0)
	chdir(client->pwd_home);
      send_command(client->fd, "250 Directory successfully changed.\r\n");
    }
  (void)server;
  return (0);
}

int	dir_cdup(t_client *client, t_server *server)
{
  free(client->cmd_buffer);
  client->cmd_buffer = strdup("..");
  dir_cwd(client, server);
  return (0);
}
