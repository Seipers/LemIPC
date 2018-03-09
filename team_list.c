/*
** team_list.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Wed Mar 29 04:36:39 2017 Sebastien Le Guischer
** Last update Sun Apr  2 17:06:11 2017 Dorian Voravong
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include "lemipc.h"

t_list_team	*create_team_list(t_player *player)
{
  t_list_team	*new;

  if ((new = malloc(sizeof(t_list_team))) == NULL)
    return (NULL);
  new->num = player->team;
  new->nb = 1;
  if ((new->players = add_player_list(NULL, player)) == NULL)
    return (NULL);
  new->next = NULL;
  return (new);
}

t_list_team	*add_team_list(t_list_team *list, t_player *player)
{
  t_list_team	*tmp;
  t_list_team	*new;

  if (list == NULL)
    return (create_team_list(player));
  tmp = list;
  while (tmp != NULL)
    {
      if (player->team == tmp->num)
	{
	  if ((tmp->players = add_player_list(tmp->players, player)) == NULL)
	    return (NULL);
	  tmp->nb = tmp->nb + 1;
	  return (list);
	}
      tmp = tmp->next;
    }
  if ((new = create_team_list(player)) == NULL)
    return (NULL);
  new->next = list;
  return (new);
}

void	clear_team(char *bin, int team)
{
  key_t	key;
  int	msg_id;

  if ((key = ftok(bin, team)) == -1
      || (msg_id = msgget(key, SHM_R | SHM_W)) == -1)
    exit(1);
  del_msg(msg_id);
}

t_list_team	*del_team(t_list_team *list, t_list_team *team, char *bin)
{
  t_list_team	*tmp;
  t_list_team	*prev;

  tmp = list;
  free(team->players);
  if (team == tmp)
    {
      list = list->next;
      free(team);
      return (list);
    }
  while (tmp != team)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  prev->next = tmp->next;
  clear_team(bin, team->num);
  free(team);
  return (list);
}

t_list_team	*rem_team_list(t_list_team *list, int pid,
			       int team, t_info *info)
{
  t_list_team	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->num == team)
	{
	  tmp->nb = tmp->nb - 1;
	  rem_player_list(&tmp->players, pid);
	  if (tmp->nb == 0)
	    list = del_team(list, tmp, info->bin);
	  return (list);
	}
      tmp = tmp->next;
    }
  return (NULL);
}
