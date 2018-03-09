/*
** map.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 12:09:13 2017 Sebastien Le Guischer
** Last update Sun Apr  2 19:43:23 2017 Dorian Voravong
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "lemipc.h"
#include "lapin.h"

void	fill_color(unsigned int color[9])
{
  color[0] = BLACK;
  color[1] = BLUE;
  color[2] = GREEN;
  color[3] = RED;
  color[4] = TEAL;
  color[5] = YELLOW;
  color[6] = WHITE;
  color[7] = PURPLE;
  color[8] = PINK;
}

void			set_pixelarray(t_info *info,
				       int *map)
{
  int			i;
  int			j;
  unsigned int		color[8];
  t_bunny_position	pos;

  i = 0;
  pos.y = 0;
  fill_color(color);
  while (i < info->height)
    {
      j = 0;
      pos.x = 0;
      while (j < info->width)
	{
	  teksquare(info->pix, &pos,
		    color[(map[i * info->width + j] + 1) % 8],
		    info->pix->clipable.clip_width / 10);
	  pos.x += info->pix->clipable.clip_width / 10;
	  j++;
	}
      pos.y += info->pix->clipable.clip_width / 10;
      i++;
    }
}

void		print_lapin(t_info *info, int *map)
{
  static int	starting = 0;

  if (starting == 0)
    {
      info->pix = bunny_new_pixelarray(1000, 1000);
      info->win = bunny_start(1000, 1000, 0, "lemIPC");
      starting = 1;
    }
  if (info->pix == NULL || info->win == NULL)
    return ;
  set_pixelarray(info, map);
  bunny_blit(&info->win->buffer, &info->pix->clipable, NULL);
  bunny_display(info->win);
}

void	print_map(t_info *info, t_referee ref)
{
  void	*addr;
  int	*map;
  int	i;

  if ((addr = shmat(info->shm_id, NULL, SHM_R)) == (void *)-1)
    exit(1);
  map = (int *)addr;
  i = 0;
  system("clear");
  while (i < info->width * info->height)
    {
      if (map[i] == -1)
	printf(".");
      else
	printf("%d", map[i]);
      i++;
      if (i % info->width == 0)
	printf("\n");
    }
  print_lapin(info, map);
  print_list(ref.teams);
}
