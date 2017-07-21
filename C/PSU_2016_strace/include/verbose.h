/*
** verbose.h for verbose.h in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace/STRACESAVE
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Apr 15 20:05:36 2017 Nicolas TROGNOT
** Last update Sun Apr 16 19:30:32 2017 alexis papadimitriou
*/

#ifndef VERBOSE_H_
# define VERBOSE_H_

int	v_basic(long long unsigned int v, int pid);
int	v_int(long long unsigned int v, int pid);
int	v_uint(long long unsigned int v, int pid);
int	v_long(long long unsigned int v, int pid);
int	v_ulong(long long unsigned int v, int pid);
int	v_string(long long unsigned int v, int pid);
int	v_vargs(long long unsigned int v, int pid);
int	v_void(long long unsigned int v, int pid);
int	v_ptr(long long unsigned int v, int pid);

#endif /* !VERBOSE_H_ */
