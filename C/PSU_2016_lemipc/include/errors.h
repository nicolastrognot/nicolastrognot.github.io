/*
** errors.h for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Tue Mar 28 13:58:21 2017 alexis papadimitriou
** Last update Sat Apr  1 14:58:26 2017 Nicolas TROGNOT
*/

#ifndef ERRORS_H_
# define ERRORS_H_
# define PTR_ERRO (void *)-1
# define BIN_USGE "Usage: %s <path_name> <team_number>\n", av[0]
# define BIN_BNUS "Usage: %s <path_name>\n", av[0]
# define ERR_INIT "Error: failed to init the client structure.\n"
# define ERR_CREA "Error: failed to create the shared memory.\n"
# define ERR_ACSS "Error: failed to access to the memory map.\n"
# define ERR_RMID "Error: failed to delete the shared memory.\n"
# define ERR_CRES "Error: failed to create the semaphore.\n"
# define ERR_SMID "Error: failed to delete the semaphore.\n"
# define ERR_CREM "Error: failed to create the message queue.\n"
# define ERR_DEMS "Error: failed to delete the message queue.\n"
# define ERR_SDLC "Error: failed to create the SDL window.\n"
# define ERR_TMCL "Error: not enough place in map for another client.\n"
# include <stdint.h>

uint64_t	rerror(const char *error_msg, uint64_t value);
void		*rperror(const char *error_msg, void *value);
void		derror(const char *error_msg);

#endif /* !ERRORS_H_ */
