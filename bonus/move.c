/*
** move.c for lemipc in /home/dorian.voravong/rendu/PSU_2016_lemipc
** 
** Made by Dorian Voravong
** Login   <dorian.voravong@epitech.net>
** 
** Started on  Sat Apr  1 02:17:54 2017 Dorian Voravong
** Last update Sat Apr  1 18:29:07 2017 Dorian Voravong
*/

#include <stdlib.h>
#include "lemipc.h"

int	can_move(t_info *info, int *map, int new_pos, int p_j)
{
  return (new_pos >= 0 && new_pos < info->width * info->height
	  && p_j < info->width && p_j >= 0
	  && map[new_pos] == -1);
}

void	change_positions(t_info *info, int pos, int new_pos, int team)
{
  leave_shm(pos, info->shm_id);
  leave_sem(pos, info->sem_id);
  use_sem(new_pos, info->sem_id);
  use_shm(new_pos, info->shm_id, team);
}

int	move_random(t_info *info, int *map, int pos, int team)
{
  int	p_i;
  int	p_j;
  int	new_pos;

  get_position(info, pos, &p_i, &p_j);
  p_i += rand() % 3 - 1;
  p_j += rand() % 3 - 1;
  new_pos = p_i * info->width + p_j;
  if (can_move(info, map, new_pos, p_j))
    {
      change_positions(info, pos, new_pos, team);
      return (new_pos);
    }
  return (pos);
}

int	move_player(t_info *info, int *map, int pos, int enemy_pos)
{
  int	p_i;
  int	p_j;
  int	e_i;
  int	e_j;
  int	team;
  int	new_pos;

  get_position(info, pos, &p_i, &p_j);
  get_position(info, enemy_pos, &e_i, &e_j);
  team = map[pos];
  p_i += (p_i < e_i) - (p_i > e_i);
  p_j += (p_j < e_j) - (p_j > e_j);
  new_pos = p_i * info->width + p_j;
  if (can_move(info, map, new_pos, p_j))
    {
      change_positions(info, pos, new_pos, team);
      return (new_pos);
    }
  else
    return (move_random(info, map, pos, team));
}
