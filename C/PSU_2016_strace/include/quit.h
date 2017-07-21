/*
** quit.h for quit.h in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace/include
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Fri Apr 14 16:40:16 2017 Nicolas TROGNOT
** Last update Sun Apr 16 19:33:20 2017 alexis papadimitriou
*/

#ifndef QUIT_H_
# define QUIT_H_

int	check_quit(const int status);
int	quit(const int pid,
	     const int program_exist,
	     const int status);

#endif /* !QUIT_H_ */
