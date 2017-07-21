/*
** file_transfer.c for file_transfer.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat May 20 21:55:21 2017 Nicolas TROGNOT
** Last update Sat May 20 21:55:39 2017 Nicolas TROGNOT
*/

#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "command_handler.h"

int		do_stor(t_client *client)
{
  struct stat	stat;
  int		fd;
  char		buffer[1];

  fd = creat(client->cmd_buffer, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  fstat(fd, &stat);
  if (fd == -1 || S_ISREG(stat.st_mode) == 0)
    send_command(client->fd, "552 Filename is a directory.\r\n");
  else
    {
      while (read(client->data_cmdfd, buffer, 1) > 0)
	write(fd, &buffer[0], 1);
      send_command(client->fd, "226 Closing data connection.\r\n");
      close(fd);
    }
  close(client->data_cmdfd);
  client->data_cmdfd = -1;
  return (0);
}

int		file_transfer_stor(t_client *client, t_server *server)
{
  if (client->data_fd == -1 ||
      (client->data_cmdfd =
       accept(client->data_fd, (struct sockaddr *)&client->data_s_in,
	      &client->data_s_len)) == -1)
    return (send_command(client->fd, "425 Use PORT or PASV first.\r\n"));
  send_command(client->fd, "150 File status okay.\r\n");
  if (strlen(client->cmd_buffer) != 0)
    do_stor(client);
  else
    send_command(client->fd, "501 No args.\r\n");
  (void)server;
  return (0);
}

int		do_retr(t_client *client)
{
  struct stat	stat;
  int		fd;
  char		buffer[1];

  fd = open(client->cmd_buffer, O_RDONLY);
  fstat(fd, &stat);
  if (fd == -1 || S_ISREG(stat.st_mode) == 0)
    send_command(client->fd, "552 Filename is a directory.\r\n");
  else
    {
      while (read(fd, buffer, 1) > 0)
	write(client->data_cmdfd, &buffer[0], 1);
      send_command(client->fd, "226 Closing data connection.\r\n");
      close(fd);
    }
  close(client->data_cmdfd);
  client->data_cmdfd = -1;
  return (0);
}

int		file_transfer_retr(t_client *client, t_server *server)
{
  if (client->data_fd == -1 ||
      (client->data_cmdfd =
       accept(client->data_fd, (struct sockaddr *)&client->data_s_in,
	      &client->data_s_len)) == -1)
    return (send_command(client->fd, "425 Use PORT or PASV first.\r\n"));
  send_command(client->fd, "150 File status okay.\r\n");
  if (strlen(client->cmd_buffer) != 0)
    do_retr(client);
  else
    send_command(client->fd, "501 No args.\r\n");
  (void)server;
  return (0);
}
