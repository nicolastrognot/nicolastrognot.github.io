/*
** main.c for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Mar 28 11:46:01 2017 alexis papadimitriou
** Last update Sun Apr  2 20:15:38 2017 Nicolas TROGNOT
*/

#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include "errors.h"
#include "loop.h"

static void		catch_sigint(int signum, t_client *_client)
{
  static t_client	*client = NULL;
  uint8_t		msg;

  if (!client)
    client = _client;
  if (signum == SIGINT)
    {
      dprintf(1, "Exiting...\n");
      msg = MSG_KILL;
      msgsnd(client->msg_id, &msg, 1, 0);
      if (client->connection_state == HOST)
	{
	  sleep(1);
	  free_client(client);
	  exit(0);
	}
    }
}

int		main(const int ac, const char **av)
{
  t_client	*client;

  if (ac < 3)
    return (0 & dprintf(1, BIN_USGE));
  srand(time(0));
  if (!(client = init_client(av[1], atoi(av[2]))))
    return (-1);
  catch_sigint(0, client);
  signal(SIGINT, (void (*)(int))catch_sigint);
  loop(client);
  free_client(client);
  return (0);
}
