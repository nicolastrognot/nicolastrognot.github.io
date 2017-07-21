/*
** struct_handler.h for struct_handler.h in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/inc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:21:23 2017 Nicolas TROGNOT
** Last update Wed May 17 11:21:46 2017 Nicolas TROGNOT
*/

#ifndef STRUCT_HANDLER_H_
# define STRUCT_HANDLER_H_

typedef struct	s_server
{
  int		port;
  char		*path;
  int		fd;
}		t_server;

t_server	*init_server(char **av);
void		free_server(t_server *myserver);

#endif /* !STRUCT_HANDLER_H_ */
