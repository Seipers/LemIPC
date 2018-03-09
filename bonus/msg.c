/*
** msg.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Wed Mar 29 05:50:52 2017 Sebastien Le Guischer
** Last update Sun Apr  2 20:30:46 2017 Sebastien Le Guischer
*/

#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include "lemipc.h"

void	send_msg(int msg_id, char *str)
{
  t_msg	msg;

  bzero(&msg, sizeof(msg));
  msg.msg_s = 35;
  sprintf(msg.msg, "%s", str);
  if ((msgsnd(msg_id, &msg, sizeof(t_msg), 0)) == -1)
    exit (1);
}

int	wait_str(int msg_id, char *str)
{
  t_msg	msg;
  int	i;

  i = 0;
  while ((msgrcv(msg_id, &msg, sizeof(t_msg), 0, IPC_NOWAIT)) == -1)
    {
      if (i > 9999999)
	return (1);
      i++;
    }
  if (strcmp(msg.msg, str) != 0)
    exit(1);
  return (0);
}

void	del_msg(int msg_id)
{
  msgctl(msg_id, IPC_RMID, NULL);
}
