/*
** client.c for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Mar 28 13:35:40 2017 alexis papadimitriou
** Last update Sun Apr  2 20:13:31 2017 Nicolas TROGNOT
*/

#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdio.h>
#include "errors.h"
#include "map.h"
#include "client_in.h"

uint8_t		get_number_team(t_map *map)
{
  uint32_t	j;
  uint32_t	i;
  uint32_t	tmp;

  j = 0;
  tmp = MAP_EMPTY;
  while (j < MAP_WIDTH)
    {
      i = 0;
      while (i < MAP_WIDTH)
	{
	  if (map->map[j][i] != MAP_EMPTY)
	    {
	      if (tmp != MAP_EMPTY && map->map[j][i] != tmp)
		return (TRUE);
	      tmp = map->map[j][i];
	    }
	  i++;
	}
      j++;
    }
  return (FALSE);
}

void		check_ok(t_client *client)
{
  struct sembuf	sops;
  uint8_t	ret;

  ret = FALSE;
  sops.sem_num = 0;
  sops.sem_flg = 0;
  while (ret == FALSE)
    {
      sops.sem_op = -1;
      semop(client->sem_id, &sops, 1);
      ret = get_number_team(client->map) && client->map->nb_client > 2;
      sops.sem_op = 1;
      semop(client->sem_id, &sops, 1);
    }
}

void		append_client(t_client *new)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_op = -1;
  sops.sem_flg = 0;
  semop(new->sem_id, &sops, 1);
  if (append_client_to_map(new->team_number, new, new->map) != 0)
    derror(ERR_TMCL);
  increment_nb_client(new->map);
  sops.sem_op = 1;
  semop(new->sem_id, &sops, 1);
}

t_client	*init_client(const char *path_name,
			     const int32_t team_number)
{
  t_client	*new;
  t_map		map;

  if ((new = malloc(sizeof(t_client))) == NULL ||
      (new->key = ftok(path_name, 0)) == -1)
    return (rperror(ERR_INIT, NULL));
  fill_base(new, team_number);
  if ((new->shm_id = shmget(new->key, sizeof(t_map), SHM_R | SHM_W)) == -1)
    {
      new->connection_state = HOST;
      if (fill_host(new) == NULL)
	return (NULL);
      semctl(new->sem_id, 0, SETVAL, 1);
      memcpy(new->map, init_map(&map), sizeof(t_map));
    }
  if ((new->map = shmat(new->shm_id, NULL, SHM_R | SHM_W)) == PTR_ERRO)
    return (rperror(ERR_ACSS, NULL));
  append_client(new);
  check_ok(new);
  return (new);
}

void		free_client(t_client *client)
{
  decrement_nb_client(client->map);
  if (client->connection_state == HOST)
    {
      if (shmctl(client->shm_id, IPC_RMID, NULL) == -1)
	dprintf(2, ERR_RMID);
      if (semctl(client->sem_id, 1, IPC_RMID) == -1)
	dprintf(2, ERR_SMID);
      if (msgctl(client->msg_id, IPC_RMID, NULL) == -1)
	dprintf(2, ERR_DEMS);
    }
  free(client);
}
