/*
** referee.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Wed Mar 29 03:33:28 2017 Sebastien Le Guischer
** Last update Sun Apr  2 20:27:03 2017 Sebastien Le Guischer
*/

#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>
#include "lemipc.h"

void	one_turn(t_referee *ref, t_info *info)
{
  send_msg(ref->players->player->msg_id, T_START);
  if (wait_str(info->msg_id, T_END) == 1)
    ref->start = 2;
  ref->players = roll_player_list(ref->players);
}

void		win(t_referee *ref, t_info *info)
{
  t_list_player	*tmp;

  tmp = ref->players;
  while (tmp->next != NULL)
    {
      send_msg(tmp->player->msg_id, WIN);
      delete_last_player(ref, info, tmp->player->team, tmp->player->pid);
      tmp = tmp->next;
    }
  send_msg(tmp->player->msg_id, QUIT);
  delete_last_player(ref, info, tmp->player->team, tmp->player->pid);
}

int		count_player(t_list_team *list)
{
  t_list_team	*tmp;
  int		nb;

  nb = 0;
  tmp = list;
  while (tmp != NULL)
    {
      nb += tmp->nb;
      tmp = tmp->next;
    }
  return (nb);
}

void	check_full_map(t_referee *ref, t_info *info)
{
  float	max;

  if (ref->start == 0)
    {
      max = (count_player(ref->teams) * 100.0) / (info->width * info->height);
      if (max > 80)
	ref->start = 2;
    }
}

void		referee(t_info *info)
{
  t_referee	referee;
  t_msg		msg;

  referee.start = 0;
  referee.nb_team = 0;
  referee.p_max = 0;
  referee.teams = NULL;
  referee.players = NULL;
  while (referee.start != 2)
    {
      while ((msgrcv(info->msg_id, &msg, sizeof(t_msg), 0, IPC_NOWAIT)) != -1)
	{
	  if (strncmp(msg.msg, ADD, strlen(ADD)) == 0)
	    add_player(msg.msg, &referee, info);
	  else if (strncmp(msg.msg, DEL, strlen(DEL)) == 0)
	    delete_player(msg.msg, &referee, info);
	}
      check_full_map(&referee, info);
      if (referee.start == 1)
	one_turn(&referee, info);
      if (referee.start == 2)
	win(&referee, info);
      print_map(info, referee);
    }
}
