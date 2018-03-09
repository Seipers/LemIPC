/*
** map.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 12:09:13 2017 Sebastien Le Guischer
** Last update Sun Apr  2 20:19:41 2017 Sebastien Le Guischer
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "lemipc.h"

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
  print_list(ref.teams);
}
