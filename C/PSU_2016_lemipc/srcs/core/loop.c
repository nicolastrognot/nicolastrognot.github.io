/*
** loop.c for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Mar 28 13:35:40 2017 alexis papadimitriou
** Last update Sun Apr  2 20:11:23 2017 Nicolas TROGNOT
*/

#include <unistd.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include "map.h"

void			do_loop(t_client *client,
				struct sembuf *sops,
				uint8_t *running)
{
  uint8_t		msg;

  if (semctl(client->sem_id, 0, GETVAL) == 1)
    {
      sops->sem_op = -1;
      semop(client->sem_id, sops, 1);
      if (client->connection_state == HOST)
	display_map(client->map);
      *running = do_turn(client);
      if (client->connection_state == HOST)
	{
	  if (get_number_team(client->map))
	    *running = TRUE;
	  else
	    {
	      msg = MSG_KILL;
	      msgsnd(client->msg_id, &msg, 1, 0);
	      sleep(1);
	    }
	}
      sops->sem_op = 1;
      semop(client->sem_id, sops, 1);
    }
}

void			loop(t_client *client)
{
  struct sembuf		sops;
  uint8_t		running;
  uint8_t		msg;

  running = TRUE;
  sops.sem_num = 0;
  sops.sem_flg = 0;
  while (running)
    {
      msg = 0;
      if ((msgrcv(client->msg_id, &msg, 1, 0, IPC_NOWAIT) != -1) &&
	  ((msg & MSG_KILL) == MSG_KILL))
	{
	  msgsnd(client->msg_id, &msg, 1, 0);
	  if (client->connection_state == HOST)
	    sleep(1);
	  return ;
	}
      do_loop(client, &sops, &running);
      usleep(200000);
    }
}
