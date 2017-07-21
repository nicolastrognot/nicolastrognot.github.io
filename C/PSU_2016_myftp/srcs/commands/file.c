/*
** file.c for file.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May 20 21:55:12 2017 Nicolas TROGNOT
** Last update Sat May 20 21:55:13 2017 Nicolas TROGNOT
*/

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "command_handler.h"

int	check_path(t_client *client, char *buffer)
{
  char	real[4096];

  memset(real, 0, 4096);
  realpath(buffer, real);
  if (strncmp(client->pwd_home, real, strlen(client->pwd_home)) != 0)
    return (1);
  return (0);
}

int	file_dele(t_client *client, t_server *server)
{
  char	buffer[4096];

  memset(buffer, 0, 4096);
  memcpy(buffer, client->cmd_buffer, strlen(client->cmd_buffer));
  if (client->cmd_buffer[0] == '/')
    {
      memset(buffer, 0, 4096);
      memcpy(buffer, client->pwd_home, strlen(client->pwd_home));
      strcat(buffer, client->cmd_buffer);
    }
  if (check_path(client, buffer) == 0 && unlink(buffer) == 0)
    {
      send_command(client->fd, "250 Deleted ");
      send_command(client->fd, client->cmd_buffer);
      send_command(client->fd, "\r\n");
    }
  else
    {
      send_command(client->fd, "550 Could not delete ");
      send_command(client->fd, client->cmd_buffer);
      send_command(client->fd, "\r\n");
    }
  (void)server;
  return (0);
}

int	file_pwd(t_client *client, t_server *server)
{
  char	buffer[4096];

  send_command(client->fd, "257 \"");
  memset(buffer, 0, 4096);
  getcwd(buffer, 4096);
  if (strcmp(buffer, client->pwd_home) == 0)
    send_command(client->fd, "/");
  else
    send_command(client->fd, buffer + strlen(client->pwd_home));
  send_command(client->fd, "\" is your current location\r\n");
  (void)server;
  return (0);
}

int	file_list(t_client *client, t_server *server)
{
  int	stdout;
  int	pid;

  if (client->data_fd == -1 ||
      (client->data_cmdfd =
       accept(client->data_fd, (struct sockaddr *)&client->data_s_in,
	      &client->data_s_len)) == -1)
    return (send_command(client->fd, "425 Use PORT or PASV first.\r\n"));
  send_command(client->fd, "150 File status okay.\r\n");
  stdout = dup(1);
  dup2(client->data_cmdfd, 1);
  if ((pid = fork()) == 0)
    execl("/bin/ls", "ls", "-la", NULL);
  dup2(stdout, 1);
  close(client->data_cmdfd);
  client->data_cmdfd = -1;
  (void)server;
  return (send_command(client->fd, "226 Closing data connection.\r\n"));
}
