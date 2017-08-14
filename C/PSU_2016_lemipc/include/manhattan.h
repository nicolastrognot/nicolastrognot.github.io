/*
** manhattan.h for manhattan.h in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sun Apr  2 13:21:32 2017 Nicolas TROGNOT
** Last update Sun Apr  2 13:28:20 2017 Nicolas TROGNOT
*/

#ifndef MANHATTAN_H_
# define MANHATTAN_H_
# include "map.h"
# include "check.h"

void	get_closest_enemy(t_client *client,
			  t_pos *next_pos,
			  int manhattan);

#endif /* !MANHATTAN_H_ */
