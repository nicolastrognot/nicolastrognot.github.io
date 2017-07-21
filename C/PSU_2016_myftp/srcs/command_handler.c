/*
** command_handler.c for command_handler.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:28:23 2017 Nicolas TROGNOT
** Last update Sat May 20 12:50:48 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "command_handler.h"

static const t_cmd	g_c[NB_CMDS] =
  {
    {"USER", &login_user},
    {"PASS", &login_pass},
    {"QUIT", &logout_quit},
    {"AUTH", &login_auth},
    {"NOOP", &misc_noop},
    {"SYST", &misc_syst},
    {"PWD", &file_pwd},
    {"TYPE", &type_type},
    {"PASV", &transfer_pasv},
    {"PORT", &transfer_port},
    {"LIST", &file_list},
    {"DELE", &file_dele},
    {"CWD", &dir_cwd},
    {"CDUP", &dir_cdup},
    {"HELP", &info_help},
    {"STOR", &file_transfer_stor},
    {"RETR", &file_transfer_retr}
  };

int	info_help(t_client *client, t_server *server)
{
  int	i;

  send_command(client->fd, "214-The following commands are recognized.\n");
  i = 0;
  while (i < NB_CMDS)
    {
      send_command(client->fd, g_c[i].str);
      if (i != NB_CMDS - 1)
	send_command(client->fd, " ");
      i++;
    }
  send_command(client->fd, "\n214 Help OK.\r\n");
  (void)server;
  return (0);
}

int	send_command(int fd, char *str)
{
  write(fd, str, strlen(str));
  return (0);
}

int	detect_command(t_client *client, t_server *server)
{
  int	i;

  i = -1;
  while (++i < NB_CMDS)
    {
      if ((strncasecmp(g_c[i].str, client->buffer, strlen(g_c[i].str))) == 0)
	{
	  client->cmd_buffer = strdup(client->buffer + strlen(g_c[i].str) + 1);
	  if (client->is_logged != 1 && i >= 3)
	    send_command(client->fd, "530 Login with USER and PASS.\r\n");
	  else
	    g_c[i].func(client, server);
	  free(client->cmd_buffer);
	  return (0);
	}
    }
  send_command(client->fd, "500 Unknown command.\r\n");
  return (0);
}
