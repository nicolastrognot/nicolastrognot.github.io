/*
** misc.c for misc.c in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump/objdump/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Feb 25 22:10:53 2017 Nicolas TROGNOT
** Last update Sat Feb 25 22:11:18 2017 Nicolas TROGNOT
*/

int			get_addr_size(unsigned long addr)
{
  unsigned long		i;
  int			j;

  i = 0x1;
  j = 0;
  while (i < addr)
    {
      i *= 0x10;
      j += 1;
    }
  if (j < 4)
    return (4);
  return (j);
}
