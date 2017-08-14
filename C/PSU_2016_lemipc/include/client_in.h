/*
** client_in.h for client_in.h in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc/include
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Mar 31 16:46:21 2017 Nicolas TROGNOT
** Last update Sat Apr  1 11:08:34 2017 Nicolas TROGNOT
*/

#ifndef CLIENT_IN_H_
# define CLIENT_IN_H_

void	increment_nb_client(t_map *map);
void	decrement_nb_client(t_map *map);
void	fill_base(t_client *client,
		  const int32_t team_number);
void	*fill_host(t_client *client);

#endif /* !CLIENT_IN_H_ */
