/*
** player_list.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Fri Mar 31 00:09:49 2017 Sebastien Le Guischer
** Last update Sat Apr  1 04:31:03 2017 Sebastien Le Guischer
*/

#include <stdlib.h>
#include "lemipc.h"

t_list_player	*create_player_list(t_player *player)
{
  t_list_player	*new;

  if ((new = malloc(sizeof(t_list_player))) == NULL)
    return (NULL);
  new->player = player;
  new->next = NULL;
  return (new);
}

t_list_player	*add_player_list(t_list_player *list, t_player *player)
{
  t_list_player	*tmp;
  t_list_player	*new;

  if (list == NULL)
    return (create_player_list(player));
  if ((new = malloc(sizeof(t_list_player))) == NULL)
    return (NULL);
  new->player = player;
  new->next = NULL;
  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
  return (list);
}

t_player	*rem_player_list(t_list_player **list, int pid)
{
  t_list_player	*tmp;
  t_player	*save;

  tmp = *list;
  if (tmp->player->pid == pid)
    {
      save = tmp->player;
      *list = tmp->next;
      return (save);
    }
  while (tmp->next != NULL)
    {
      if (tmp->next->player->pid == pid)
	{
	  save = tmp->next->player;
	  tmp->next = tmp->next->next;
	  return (save);
	}
      tmp = tmp->next;
    }
  return (NULL);
}

t_list_player	*roll_player_list(t_list_player *list)
{
  t_list_player	*save;
  t_list_player	*tmp;
  t_list_player	*ptr;

  save = list;
  ptr = list->next;
  tmp = list->next;
  while (tmp->next != NULL)
    tmp = tmp->next;
  save->next = NULL;
  tmp->next = save;
  return (ptr);
}
