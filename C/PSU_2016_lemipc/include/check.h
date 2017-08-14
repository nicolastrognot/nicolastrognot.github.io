/*
** check.c for check.c in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc/srcs/core
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Mar 31 16:58:33 2017 Nicolas TROGNOT
** Last update Sun Apr  2 20:03:21 2017 Nicolas TROGNOT
*/

#ifndef CHECK_H_
# define CHECK_H_

uint8_t		check_neighbours(t_client *client);
uint8_t		check_enemy(t_map *map, uint32_t team_number,
			    t_pos *pos);

#endif /* !CHECK_H_ */
