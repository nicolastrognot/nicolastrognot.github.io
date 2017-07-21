/*
** transfer.c for transfer.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs/commands
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:58:03 2017 Nicolas TROGNOT
** Last update Sun May 21 19:56:43 2017 Nicolas TROGNOT
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "misc.h"
#include "command_handler.h"

void			pasv_echo(char *buffer, t_client *client,
				  struct sockaddr_in s_in)
{
  memset(buffer, 0, 4096);
  sprintf(buffer, "227 Entering passive mode (%s,%d,%d).\r\n",
	  replace_str(client->ip_server, "127.0.0.1", '.', ','),
	  ntohs(s_in.sin_port) / 256,
	  ntohs(s_in.sin_port) % 256);
  send_command(client->fd, buffer);
}

int			transfer_pasv(t_client *client, t_server *server)
{
  struct protoent	*pe;
  char			buffer[4096];

  client->data_s_in.sin_family = AF_INET;
  client->data_s_in.sin_port = 0;
  client->data_s_in.sin_addr.s_addr = INADDR_ANY;
  if ((pe = getprotobyname("TCP")) == NULL ||
      (client->data_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1 ||
      bind(client->data_fd, (const struct sockaddr *)&client->data_s_in,
	   sizeof(client->data_s_in)) ==
      -1 || listen(client->data_fd, 1) == -1)
    {
      close(client->data_fd);
      send_command(client->fd, "500 Could not create the data socket\r\n");
      return (0);
    }
  client->data_s_len = sizeof(client->data_s_in);
  getsockname(client->data_fd, (struct sockaddr *)&client->data_s_in,
	      &client->data_s_len);
  pasv_echo(buffer, client, client->data_s_in);
  (void)server;
  return (0);
}

int			transfer_port_p(char *cmd)
{
  int			port;
  char			*str;
  int			i;

  i = -1;
  port = 0;
  str = strtok(cmd, ",");
  while (str != NULL && ++i >= 0)
    {
      if (i == 4)
	port = atoi(str) * 256;
      if (i == 5)
	port += atoi(str);
      str = strtok(NULL, ",");
    }
  printf("%d\n", port);
  return (port);
}

char			*transfer_port_a(char *cmd)
{
  char			*ret;
  char			*str;
  int			i;

  i = -1;
  if ((ret = malloc(25)) == NULL)
    return ("127.0.0.1");
  memset(ret, 0, 25);
  str = strtok(cmd, ",");
  while (str != NULL && ++i < 4)
    {
      strcat(ret, str);
      if (i != 3)
	strcat(ret, ".");
      str = strtok(NULL, ",");
    }
  printf("%s\n", ret);
  return (ret);
}

int			transfer_port(t_client *client, t_server *server)
{
  struct protoent	*pe;

  client->data_s_in.sin_family = AF_INET;
  client->data_s_in.sin_port =
    htons(transfer_port_p(strdup(client->cmd_buffer)));
  client->data_s_in.sin_addr.s_addr =
    inet_addr(transfer_port_a(strdup(client->cmd_buffer)));
  if ((pe = getprotobyname("TCP")) == NULL ||
      (client->data_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1 ||
      bind(client->data_fd, (const struct sockaddr *)&client->data_s_in,
	   sizeof(client->data_s_in)) ==
      -1 || listen(client->data_fd, 1) == -1)
    {
      close(client->data_fd);
      send_command(client->fd, "500 Could not create the data socket\r\n");
      return (0);
    }
  send_command(client->fd, "200 Port command successful\r\n");
  (void)server;
  return (0);
}
