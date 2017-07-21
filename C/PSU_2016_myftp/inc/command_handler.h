/*
** command_handler.h for command_handler.h in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:17:40 2017 Nicolas TROGNOT
** Last update Wed May 17 11:18:17 2017 Nicolas TROGNOT
*/

#ifndef COMMAND_HANDLER_H_
# define COMMAND_HANDLER_H_
# define NB_CMDS 17
# include "struct_handler.h"
# include "client_handler.h"

typedef struct	s_cmd
{
  char		*str;
  int		(*func)(t_client *, t_server *);
}		t_cmd;

int		info_help(t_client *, t_server *);
int		detect_command(t_client *, t_server *);
int		send_command(int, char *);
int		login_user(t_client *, t_server *);
int		login_pass(t_client *, t_server *);
int		login_auth(t_client *, t_server *);
int		misc_syst(t_client *, t_server *);
int		misc_noop(t_client *, t_server *);
int		file_pwd(t_client *, t_server *);
int		file_list(t_client *, t_server *);
int		file_dele(t_client *, t_server *);
int		logout_quit(t_client *, t_server *);
int		type_type(t_client *, t_server *);
int		transfer_pasv(t_client *, t_server *);
int		file_transfer_stor(t_client *, t_server *);
int		file_transfer_retr(t_client *, t_server *);
int		transfer_port(t_client *, t_server *);
int		dir_cwd(t_client *, t_server *);
int		dir_cdup(t_client *, t_server *);

#endif /* !COMMAND_HANDLER_H_ */
