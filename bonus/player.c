/*
** player.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 04:51:45 2017 Sebastien Le Guischer
** Last update Sun Apr  2 17:20:29 2017 Dorian Voravong
*/

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "lemipc.h"

t_player	*create_player(int team, int pid, char *key_str)
{
  t_player	*new;
  key_t		key;

  if ((new = malloc(sizeof(t_player))) == NULL)
    return (NULL);
  new->team = team;
  new->pid = pid;
  if ((key = ftok(key_str, pid)) == -1
      || (new->msg_id = msgget(key, SHM_W | SHM_R)) == -1)
    return (NULL);
  return (new);
}

int	get_team_id(char *msg)
{
  int	i;

  i = 0;
  while (msg[i] != '/')
    i++;
  return (atoi(msg + i + 1));
}

void		add_player(char *msg, t_referee *ref, t_info *info)
{
  t_player	*player;
  int		pid;
  int		team_id;

  pid = atoi(msg + strlen(ADD));
  team_id = get_team_id(msg);
  if ((player = create_player(team_id, pid, info->bin)) == NULL
      || (ref->teams = add_team_list(ref->teams, player)) == NULL
      || (ref->players = add_player_list(ref->players, player)) == NULL)
    exit(1);
  update_team_info(ref);
  send_msg(player->msg_id, OK);
}

void		delete_player(char *msg, t_referee *ref, t_info *info)
{
  int		pid;
  int		team_id;
  t_player	*player;

  pid = atoi(msg + strlen(DEL));
  team_id = get_team_id(msg);
  if ((ref->teams = rem_team_list(ref->teams, pid, team_id, info)) == NULL
      || (player = rem_player_list(&ref->players, pid)) == NULL)
    exit(1);
  free(player);
  update_team_info(ref);
}

void		delete_last_player(t_referee *ref, t_info *info,
				   int team_id, int pid)
{
  t_player	*player;

  if ((ref->teams = rem_team_list(ref->teams, pid, team_id, info)) == NULL
      || (player = rem_player_list(&ref->players, pid)) == NULL)
    exit(1);
  free(player);
  update_team_info(ref);
}
