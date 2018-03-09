/*
** user.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Fri Mar 31 01:52:34 2017 Sebastien Le Guischer
** Last update Sun Apr  2 20:28:13 2017 Sebastien Le Guischer
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "lemipc.h"

int	get_msg_id_team(char *bin, int team)
{
  int	msg_id;
  key_t	key;

  key = ftok(bin, team);
  if ((msg_id = msgget(key, SHM_W | SHM_R)) == -1)
    if ((msg_id = msgget(key, IPC_CREAT | SHM_W | SHM_R)) == -1)
      exit(1);
  return (msg_id);
}

int	create_loc_msg(char *bin, int team, int msg_id)
{
  char	msg[100];
  key_t	key;
  int	pid;
  int	msg_id_l;

  pid = getpid();
  key = ftok(bin, pid);
  if ((msg_id_l = msgget(key, IPC_CREAT | SHM_W | SHM_R)) == -1)
    exit(1);
  sprintf(msg, "%s%d/%d", ADD, pid, team);
  send_msg(msg_id, msg);
  return (msg_id_l);
}

int	user(t_info *info, int team)
{
  int	pos;
  int	msg_id[2];

  msg_id[0] = create_loc_msg(info->bin, team, info->msg_id);
  msg_id[1] = get_msg_id_team(info->bin, team);
  if (wait_str(msg_id[0], OK) == 1)
    {
      del_msg(msg_id[0]);
      return (-1);
    }
  pos = rand() % (info->width * info->height);
  while (use_sem(pos, info->sem_id) == -1)
    pos = rand() % (info->width * info->height);
  use_shm(pos, info->shm_id, team);
  ia(info, msg_id, team, pos);
  del_msg(msg_id[0]);
  return (0);
}
