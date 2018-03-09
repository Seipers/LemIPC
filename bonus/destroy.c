/*
** destroy.c for lemipc in /home/dorian.voravong/rendu/PSU_2016_lemipc
** 
** Made by Dorian Voravong
** Login   <dorian.voravong@epitech.net>
** 
** Started on  Sat Apr  1 02:16:28 2017 Dorian Voravong
** Last update Sun Apr  2 17:17:36 2017 Dorian Voravong
*/

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include "lemipc.h"

void		destroy(t_info *info, int pos)
{
  int		pid;
  int		msg_id;
  key_t		key;

  if ((pid = semctl(info->sem_id, pos, GETPID)) == -1
      || (key = ftok(info->bin, pid)) == -1
      || (msg_id = msgget(key, SHM_W | SHM_R)) == -1)
    exit(1);
  send_msg(msg_id, DESTROY);
}

void	check_destroy(t_info *info, int *map, int pos, int team)
{
  int	i;
  int	j;
  int	c;

  c = 0;
  get_position(info, pos, &i, &j);
  i--;
  j--;
  while (c != 8)
    {
      if (i >= 0 && j >= 0 && i < info->width && j < info->height)
	{
	  if (map[i * info->width + j] != -1
	      && map[i * info->width + j] != team
	      && search_team(info, map, team, i * info->width + j) > 1)
	    destroy(info, i * info->width + j);
	}
      i = i + (c == 2 || c == 3) - (c == 6 || c == 7);
      j = j + (c == 0 || c == 1) - (c == 4 || c == 5);
      c++;
    }
}

int	search_team(t_info *info, int *map, int team, int pos)
{
  int	i;
  int	j;
  int	c;
  int	nb;

  c = 0;
  nb = 0;
  get_position(info, pos, &i, &j);
  i--;
  j--;
  while (c != 8)
    {
      if (i >= 0 && j >= 0 && i < info->height && j < info->width)
	{
	  if (map[i * info->width + j] == team)
	    nb++;
	}
      i = i + (c == 2 || c == 3) - (c == 6 || c == 7);
      j = j + (c == 0 || c == 1) - (c == 4 || c == 5);
      c++;
    }
  return (nb);
}
