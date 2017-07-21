/*
** verbose_bis.c for verbose_bis.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace/STRACESAVE
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sun Apr 16 13:48:43 2017 Nicolas TROGNOT
** Last update Sun Apr 16 20:00:05 2017 alexis papadimitriou
*/

#include <sys/ptrace.h>
#include <stdio.h>

int	v_string(long long unsigned int v,
		 int pid)
{
  char	c;
  int	ret;
  int	n;

  n = 0;
  ret = 0;
  dprintf(2, "\"");
  while ((c = ptrace(PTRACE_PEEKTEXT, pid, v + ret, NULL)) &&
	 (ret < 64))
    {
      if (c == '\n')
	n += dprintf(2, "\\n");
      else if (c >= 33 && c <= 126)
	n += dprintf(2, "%c", c);
      else
	n += dprintf(2, "\\%d", c);
      ret++;
    }
  dprintf(2, "\"");
  if (ret == 64 &&
      ptrace(PTRACE_PEEKTEXT, pid, v + ret, NULL))
    n += dprintf(2, "...");
  n += 2;
  return (n);
}

int	v_vargs(long long unsigned int v)
{
  (void)v;
  return (dprintf(2, "..."));
}

int	v_void(long long unsigned int v)
{
  (void)v;
  return (dprintf(2, "?"));
}

int	v_ptr(long long unsigned int v)
{
  if (v == 0)
    return (dprintf(2, "NULL"));
  return (dprintf(2, "%p", (void *)v));
}
