/*
** file_handler.c for file_handler.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/nm
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Mon Feb 20 11:02:39 2017 Nicolas TROGNOT
** Last update Sat Feb 25 22:04:34 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int		file_size(int fd)
{
  int		size;

  size = lseek(fd, 0, SEEK_END);
  return (size);
}

int		open_file(const char *filename)
{
  int		fd;

  if ((fd = open(filename, O_RDONLY)) < 0)
    printf("objdump: '%s': No such file\n", filename);
  return (fd);
}
