/*
** client_turn.c for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc/srcs
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Thu Mar 30 13:22:06 2017 alexis papadimitriou
** Last update Sun Apr  2 20:10:48 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include "manhattan.h"

static uint8_t	is_empty(t_map *map, t_pos *pos)
{
  if ((int8_t)pos->x < 0 || pos->x > MAP_WIDTH - 1 ||
      (int8_t)pos->y < 0 || pos->y > MAP_WIDTH - 1)
    return (FALSE);
  return (map->map[pos->y][pos->x] == MAP_EMPTY);
}

static void	set_pos(t_client *client, t_pos *new_pos)
{
  client->map->map[client->pos.y][client->pos.x] = MAP_EMPTY;
  client->pos.x = new_pos->x;
  client->pos.y = new_pos->y;
  client->map->map[client->pos.y][client->pos.x] = client->team_number;
}

static uint8_t	try_move(t_client *client)
{
  uint8_t	moved;
  t_pos		next_pos;

  get_closest_enemy(client, &next_pos, 0);
  if (client->map->map[next_pos.y][next_pos.x] != MAP_EMPTY ||
      client->team_number % 2)
    {
      next_pos.x = client->pos.x + (rand() % 3) - 1;
      next_pos.y = client->pos.y + (rand() % 3) - 1;
    }
  moved = is_empty(client->map, &next_pos);
  if (moved)
    set_pos(client, &next_pos);
  return (moved);
}

static void	move(t_client *client)
{
  uint8_t	moved;

  moved = FALSE;
  while (!moved)
    moved = try_move(client);
}

uint8_t		do_turn(t_client *client)
{
  if (client->status == DEAD || check_neighbours(client))
    {
      if (client->status != DEAD)
	client->map->map[client->pos.y][client->pos.x] = MAP_EMPTY;
      client->status = DEAD;
      return (FALSE);
    }
  move(client);
  return (TRUE);
}
