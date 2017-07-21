/*
** client_handler.h for client_handler.h in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:16:29 2017 Nicolas TROGNOT
** Last update Sat May 20 12:29:40 2017 Nicolas TROGNOT
*/

#ifndef CLIENT_HANDLER_H_
# define CLIENT_HANDLER_H_
# include <netdb.h>
# include <stdio.h>
# include "struct_handler.h"

typedef struct		s_client
{
  pid_t			pid;
  char			*buffer;
  char			*cmd_buffer;
  int			fd;
  FILE			*file;
  int			data_fd;
  int			data_cmdfd;
  struct sockaddr_in	data_s_in;
  socklen_t		data_s_len;
  char			stop;
  char			is_logged;
  char			*username;
  char			*ip_server;
  char			pwd_home[4096];
}			t_client;

int			fork_client(t_server *server,
				    int fd,
				    struct sockaddr_in *s_in_c);

#endif /* !CLIENT_HANDLER_H_ */
