/*
** team.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 12:36:35 2017 Sebastien Le Guischer
** Last update Sun Apr  2 17:22:54 2017 Dorian Voravong
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lemipc.h"

void		update_team_info(t_referee *ref)
{
  t_list_team	*tmp;
  int		nb_team;

  tmp = ref->teams;
  nb_team = 0;
  while (tmp != NULL)
    {
      if (tmp->nb > ref->p_max)
	ref->p_max = tmp->nb;
      nb_team++;
      tmp = tmp->next;
    }
  ref->nb_team = nb_team;
  if (nb_team >= 2 && ref->p_max >= 2)
    ref->start = 1;
  if (ref->start == 1 && nb_team == 1)
    ref->start = 2;
}

void		print_list(t_list_team *list)
{
  t_list_team	*tmp;

  tmp = list;
  printf("\n\n");
  while (tmp != NULL)
    {
      printf("Team %d id here with %d players\n", tmp->num, tmp->nb);
      tmp = tmp->next;
    }
  usleep(100000);
}
