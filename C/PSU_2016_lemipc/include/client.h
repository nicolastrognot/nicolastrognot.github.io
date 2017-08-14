/*
** client.h for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Mar 28 11:49:34 2017 alexis papadimitriou
** Last update Sun Apr  2 20:01:27 2017 Nicolas TROGNOT
*/

#ifndef CLIENT_H_
# define CLIENT_H_
# define MSG_KILL 0b00000001
# define ABS(x) ((x < 0) ? (-x) : (x))
# define CLIENT 0
# define HOST 1
# define ALIVE 0
# define DEAD 1
# define FALSE 0
# define TRUE 1
# include <stdint.h>
# include "map.h"

typedef struct	s_map t_map;

typedef struct	s_pos
{
  uint8_t	x;
  uint8_t	y;
}		t_pos;

typedef struct	s_client
{
  key_t		key;
  uint32_t	team_number;
  int32_t	shm_id;
  int32_t	sem_id;
  int32_t	msg_id;
  uint8_t	connection_state;
  uint8_t	status;
  t_map		*map;
  t_pos		pos;
}		t_client;

t_client	*init_client(const char *path_name,
			     const int32_t team_number);
void		free_client(t_client *client);
uint8_t		do_turn(t_client *client);
uint8_t		get_number_team(t_map *map);

#endif /* !CLIENT_H_ */
