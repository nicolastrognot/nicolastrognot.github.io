/*
** misc.c for misc.c in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Wed May 17 11:39:00 2017 Nicolas TROGNOT
** Last update Wed May 17 11:39:11 2017 Nicolas TROGNOT
*/

#include <stdlib.h>

char	*replace_str(char *in, char *d, char r, char n)
{
  int	i;

  i = 0;
  if (in == NULL)
    return (d);
  while (in[i] != '\0')
    {
      if (in[i] == r)
	in[i] = n;
      i++;
    }
  return (in);
}
