/*
** misc.c for misc.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Thu Feb 23 09:09:00 2017 Nicolas TROGNOT
** Last update Sun Feb 26 00:30:59 2017 Nicolas TROGNOT
*/

#include "misc.h"

int		my_is_alphanum(char c)
{
  if (c >= 'A' && c <= 'Z')
    return (1);
  if (c >= 'a' && c <= 'z')
    return (1);
  if (c >= '0' && c <= '9')
    return (1);
  return (0);
}

int		my_strlen_spec(char *str)
{
  int		i;
  int		ret;

  i = 0;
  ret = 0;
  while (str[i] != '\0')
    {
      if (my_is_alphanum(str[i]) == 1)
	ret++;
      i++;
    }
  return (ret);
}

int		my_charcmp(char c1, char c2)
{
  if (tolower(c1) > tolower(c2))
    return (1);
  if (tolower(c2) > tolower(c1))
    return (-1);
  return (0);
}

int		my_strcasecmp(char *str1, char *str2)
{
  int		i;
  int		j;

  i = -1;
  j = -1;
  while (str1[++i] != '\0' && str2[++j] != '\0')
    {
      while (str1[i] != '\0' && my_is_alphanum(str1[i]) == 0)
	i++;
      while (str2[j] != '\0' && my_is_alphanum(str2[j]) == 0)
	j++;
      if (my_charcmp(str1[i], str2[j]) != 0)
	return (my_charcmp(str1[i], str2[j]));
    }
  if (my_strlen_spec(str1) == my_strlen_spec(str2))
    {
      if (strlen(str1) > strlen(str2))
	return (-1);
      if (strlen(str1) < strlen(str2))
	return (1);
    }
  return (my_charcmp(str1[i], str2[j]));
}
