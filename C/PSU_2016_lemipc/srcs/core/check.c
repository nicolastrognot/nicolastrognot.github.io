/*
** check.c for check.c in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc/srcs/core
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Mar 31 16:56:11 2017 Nicolas TROGNOT
** Last update Sun Apr  2 20:10:17 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include "map.h"

static uint32_t	check_enemy(t_map *map, uint32_t team_number, t_pos *pos)
{
  if ((int8_t)pos->x < 0 || pos->x > MAP_WIDTH - 1 ||
      (int8_t)pos->y < 0 || pos->y > MAP_WIDTH - 1)
    return (MAP_EMPTY);
  return ((map->map[pos->y][pos->x] != MAP_EMPTY &&
	   map->map[pos->y][pos->x] != team_number) ?
	  (map->map[pos->y][pos->x]) : (MAP_EMPTY));
}

static uint8_t	will_die(uint32_t *neighbours, uint32_t team_number)
{
  uint8_t	i;
  uint8_t	j;

  j = -1;
  while (++j < 7)
    {
      i = j;
      while (++i < 8)
	{
	  if (neighbours[j] != MAP_EMPTY && neighbours[j] != team_number &&
	      neighbours[j] == neighbours[i])
	    return (TRUE);
	}
    }
  return (FALSE);
}

uint8_t		check_neighbours(t_client *client)
{
  uint32_t	neighbours[8];
  t_pos		check;

  check = client->pos;
  check.y -= 1;
  check.x -= 1;
  neighbours[0] = check_enemy(client->map, client->team_number, &check);
  check.x += 1;
  neighbours[1] = check_enemy(client->map, client->team_number, &check);
  check.x += 1;
  neighbours[2] = check_enemy(client->map, client->team_number, &check);
  check.y += 1;
  check.x -= 2;
  neighbours[3] = check_enemy(client->map, client->team_number, &check);
  check.x += 2;
  neighbours[4] = check_enemy(client->map, client->team_number, &check);
  check.y += 1;
  check.x -= 2;
  neighbours[5] = check_enemy(client->map, client->team_number, &check);
  check.x += 1;
  neighbours[6] = check_enemy(client->map, client->team_number, &check);
  check.x += 1;
  neighbours[7] = check_enemy(client->map, client->team_number, &check);
  return (will_die(neighbours, client->team_number));
}
