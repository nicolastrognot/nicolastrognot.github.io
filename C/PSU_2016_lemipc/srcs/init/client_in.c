/*
** client_in.c for client_in.c in /home/nicolas.trognot/rendu/Unix/PSU_2016_lemipc
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Mar 31 16:44:14 2017 Nicolas TROGNOT
** Last update Sun Apr  2 20:14:26 2017 Nicolas TROGNOT
*/

#include <stdlib.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include "errors.h"
#include "map.h"

void		increment_nb_client(t_map *map)
{
  map->nb_client++;
}

void		decrement_nb_client(t_map *map)
{
  map->nb_client--;
}

void		fill_base(t_client *client,
			  const int32_t team_number)
{
  client->team_number = team_number;
  client->connection_state = CLIENT;
  client->status = ALIVE;
  client->sem_id = semget(client->key, 1, SHM_R | SHM_W);
  client->msg_id = msgget(client->key, SHM_R | SHM_W);
}

void		*fill_host(t_client *client)
{
  if ((client->shm_id = shmget(client->key, sizeof(t_map),
			       IPC_CREAT | SHM_R | SHM_W)) == -1)
    return (rperror(ERR_CREA, NULL));
  if (((client->sem_id =
	semget(client->key, 1, IPC_CREAT | SHM_R | SHM_W))) == -1)
    return (rperror(ERR_CRES, NULL));
  if ((client->msg_id = msgget(client->key, IPC_CREAT | SHM_R | SHM_W)) == -1)
    return (rperror(ERR_CREM, NULL));
  if ((client->map = shmat(client->shm_id, NULL, SHM_R | SHM_W)) == PTR_ERRO)
    return (rperror(ERR_ACSS, NULL));
  return (client);
}
