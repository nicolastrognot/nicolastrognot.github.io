/*
** manhattan.c for manhattan.c in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sun Apr  2 13:06:19 2017 Nicolas TROGNOT
** Last update Sun Apr  2 20:11:49 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include "map.h"

void		get_closest_enemy_in(t_client *client,
				     t_pos *tmp,
				     int manhattan)
{
  int		y;
  int		x;

  y = -1;
  while (++y < MAP_WIDTH)
    {
      x = -1;
      while (++x < MAP_WIDTH)
	{
	  if (client->map->map[y][x] != MAP_EMPTY &&
	      client->map->map[y][x] != client->team_number &&
	      ((manhattan == 0) ||
	       ABS(client->pos.x - x) + ABS(client->pos.y - y) < manhattan))
	    {
	      manhattan = ABS(client->pos.x - x) +
		ABS(client->pos.y - y);
	      tmp->x = x;
	      tmp->y = y;
	    }
	}
    }
}

void		get_closest_enemy(t_client *client,
				  t_pos *next_pos,
				  int manhattan)
{
  t_pos		tmp;

  tmp.x = 0;
  tmp.y = 0;
  get_closest_enemy_in(client, &tmp, manhattan);
  if (tmp.x == client->pos.x)
    next_pos->x = client->pos.x;
  else
    next_pos->x = client->pos.x + ((tmp.x < client->pos.x) ? (-1) : (1));
  if (tmp.y == client->pos.y)
    next_pos->y = client->pos.y;
  else
    next_pos->y = client->pos.y + ((tmp.y < client->pos.y) ? (-1) : (1));
}
