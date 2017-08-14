/*
** gui.c for bonus in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc/bonus
**
** Made by alexis papadimitriou
** Login   <papadi_a@epitech.net>
**
** Started on  Sat Apr  1 12:28:13 2017 alexis papadimitriou
** Last update Sun Apr  2 21:00:40 2017 alexis papadimitriou
*/

#include <sys/shm.h>
#include <SDL/SDL.h>
#include "errors.h"
#include "map.h"

static void	putpixel(SDL_Surface *pix, int32_t x, int32_t y, uint32_t c)
{
  if (x > -1 && y > -1 && x < (MAP_WIDTH * 15) && y < (MAP_WIDTH * 15))
    ((uint32_t *)(pix->pixels))[x + y * (MAP_WIDTH * 15)] = c;
}

static void	clear(SDL_Surface *pix, uint32_t c)
{
  int		i;

  i = -1;
  while (++i < pix->w * pix->h)
    ((uint32_t *)(pix->pixels))[i] = c;
}

static void	display(SDL_Surface *screen,
			t_map *map)
{
  SDL_Event	event;
  uint8_t	running;
  int		x;
  int		y;

  running = TRUE;
  while (running)
    {
      while (SDL_PollEvent(&event))
	if (event.type == SDL_QUIT ||
	    (event.type == SDL_KEYDOWN &&
	     event.key.keysym.sym == SDLK_ESCAPE))
	  running = FALSE;
      y = -1;
      while (++y < MAP_WIDTH * 15)
	{
	  x = -1;
	  while (++x < MAP_WIDTH * 15)
	    if (map->map[y / 15][x / 15] != MAP_EMPTY)
	      putpixel(screen, x, y, (map->map[y / 15][x / 15] * 500000) %
		       0xffffff);
	}
      SDL_Flip(screen);
      clear(screen, 0);
    }
}

int		main(int ac, char **av)
{
  SDL_Surface	*screen;
  t_map		*map;
  int		shm_id;
  int		key;

  if (ac < 2)
    return (0 & dprintf(1, BIN_BNUS));
  if ((key = ftok(av[1], 0)) == -1 ||
      (shm_id = shmget(key, sizeof(t_map), SHM_R | SHM_W)) == -1 ||
      (map = shmat(shm_id, NULL, SHM_R | SHM_W)) == PTR_ERRO ||
      (SDL_Init(SDL_INIT_VIDEO) == -1) ||
      (screen = SDL_SetVideoMode(MAP_WIDTH * 15, MAP_WIDTH * 15,
				 0, SDL_DOUBLEBUF)) == NULL)
    {
      dprintf(2, "%s", ERR_SDLC);
      return (1);
    }
  SDL_WM_SetCaption("Bonus graphique lemipc", NULL);
  display(screen, map);
  SDL_FreeSurface(screen);
  SDL_Quit();
  return (0);
}
