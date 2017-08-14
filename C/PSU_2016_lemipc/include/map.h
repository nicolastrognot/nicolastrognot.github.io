/*
** map.h for map.h in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed Mar 29 15:51:28 2017 Nicolas TROGNOT
** Last update Sat Apr  1 11:09:07 2017 Nicolas TROGNOT
*/

#ifndef MAP_H_
# define MAP_H_
# define MAP_WIDTH 15
# define MAP_EMPTY (unsigned)-1
# include "client.h"

typedef struct		s_client t_client;

typedef struct		s_map
{
  uint32_t		nb_client;
  uint32_t		map[MAP_WIDTH][MAP_WIDTH];
}			t_map;

t_map			*init_map(t_map *map);
void			display_map(t_map *map);
uint8_t			append_client_to_map(const int32_t team_number,
					     t_client *client,
					     t_map *map);
uint8_t			check_map(t_map *map);

#endif /* !MAP_H_ */
