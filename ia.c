/*
** ia.c for lemicp in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 14:03:40 2017 Sebastien Le Guischer
** Last update Sun Apr  2 17:18:54 2017 Dorian Voravong
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

int		perso_msg(t_info *info, int msg_id, int team)
{
  t_msg		msg_received;
  char		msg_to_send[35];

  if ((msgrcv(msg_id, &msg_received, sizeof(t_msg), 0, 0)) == -1)
    exit(1);
  if (strcmp(msg_received.msg, T_START) == 0)
    return (0);
  if (strcmp(msg_received.msg, QUIT) == 0)
    {
      del_msg(info->msg_id);
      del_sem(info->sem_id);
      del_shm(info->shm_id);
      return (1);
    }
  if (strcmp(msg_received.msg, WIN) == 0)
    return (1);
  if (strcmp(msg_received.msg, DESTROY) != 0)
    exit(1);
  sprintf(msg_to_send, "%s%d/%d", DEL, getpid(), team);
  send_msg(info->msg_id, msg_to_send);
  return (1);
}

void	get_position(t_info *info, int pos, int *i, int *j)
{
  *i = pos / info->width;
  *j = pos % info->width;
}

int	find_enemy(t_info *info, int *map, int team, int pos)
{
  int	i;
  int	j;
  int	ratio;
  int	square[2][2];

  get_position(info, pos, &i, &j);
  ratio = 1;
  while (ratio < info->width + 1)
    {
      square[0][0] = i - ratio;
      square[0][1] = j - ratio;
      square[1][0] = i + ratio;
      square[1][1] = j + ratio;
      if ((pos = check_map(info, map, square, team)) != -1)
	return (pos);
      ratio++;
    }
  return (-1);
}

void	send_team_message(char msg_to_send[35], int enemy_pos, int msg_id)
{
  sprintf(msg_to_send, "%d", enemy_pos);
  send_msg(msg_id, msg_to_send);
}

void		ia(t_info *info, int msg_id[2], int team, int pos)
{
  t_msg		msg_received;
  int		enemy_pos;
  int		*map;
  char		msg_to_send[35];

  while (perso_msg(info, msg_id[0], team) != 1)
    {
      if (msgrcv(msg_id[1], &msg_received,
		 sizeof(t_msg), 0, IPC_NOWAIT) == -1)
	{
	  if ((map = (int *)shmat(info->shm_id, NULL, SHM_R)) == (int *)-1)
	    exit(1);
	  enemy_pos = find_enemy(info, map, team, pos);
	  if (search_team(info, map, team, pos) == 0)
	    enemy_pos = pos;
	  send_team_message(msg_to_send, enemy_pos, msg_id[1]);
	}
      else
	enemy_pos = atoi(msg_received.msg);
      pos = move_player(info, map, pos, enemy_pos);
      check_destroy(info, map, pos, team);
      send_msg(info->msg_id, T_END);
    }
  leave_shm(pos, info->shm_id);
  leave_sem(pos, info->sem_id);
}
