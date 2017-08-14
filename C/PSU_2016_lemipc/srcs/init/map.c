/*
** map.c for map.c in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed Mar 29 16:10:27 2017 Nicolas TROGNOT
** Last update Sat Apr  1 11:15:29 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

uint8_t		check_map(t_map *map)
{
  int		i;
  int		j;

  i = 0;
  while (i < MAP_WIDTH)
    {
      j = 0;
      while (j < MAP_WIDTH)
	{
	  if (map->map[i][j] == MAP_EMPTY)
	    return (1);
	  j++;
	}
      i++;
    }
  return (0);
}

uint8_t		append_client_to_map(const int32_t team_number,
				     t_client *client,
				     t_map *map)
{
  int32_t	i;
  int32_t	j;

  if (check_map(map) == 1)
    {
      i = rand() % MAP_WIDTH;
      j = rand() % MAP_WIDTH;
      while (map->map[i][j] != MAP_EMPTY)
	{
	  i = rand() % MAP_WIDTH;
	  j = rand() % MAP_WIDTH;
	}
      map->map[i][j] = team_number;
      client->pos.y = i;
      client->pos.x = j;
      return (0);
    }
  return (1);
}

t_map		*init_map(t_map *map)
{
  int		i;
  int		j;

  i = 0;
  while (i < MAP_WIDTH)
    {
      j = 0;
      while (j < MAP_WIDTH)
	{
	  map->map[i][j] = MAP_EMPTY;
	  j++;
	}
      i++;
    }
  map->nb_client = 0;
  return (map);
}

void		display_map(t_map *map)
{
  int		i;
  int		j;

  dprintf(1, "\033c");
  i = 0;
  while (i < MAP_WIDTH)
    {
      j = 0;
      while (j < MAP_WIDTH)
	{
	  if (map->map[i][j] == MAP_EMPTY)
	    dprintf(1, ". ");
	  else
	    dprintf(1, "%d ", map->map[i][j]);
	  j++;
	}
      dprintf(1, "\n");
      i++;
    }
}
