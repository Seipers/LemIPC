/*
** sem.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 11:34:20 2017 Sebastien Le Guischer
** Last update Sun Apr  2 17:22:19 2017 Dorian Voravong
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "lemipc.h"

int	set_default_sem(t_info *info)
{
  int	i;

  i = 0;
  while (i < info->width * info->height)
    {
      if (semctl(info->sem_id, i, SETVAL, 1) == -1)
	return (-1);
      i++;
    }
  return (0);
}

int		use_sem(int pos, int sem_id)
{
  struct sembuf	spos;

  spos.sem_num = pos;
  spos.sem_flg = IPC_NOWAIT;
  spos.sem_op = -1;
  if (semop(sem_id, &spos, 1) == -1)
    return (-1);
  return (0);
}

int		leave_sem(int pos, int sem_id)
{
  struct sembuf	spos;

  spos.sem_num = pos;
  spos.sem_flg = 0;
  spos.sem_op = 1;
  if (semop(sem_id, &spos, 1) == -1)
    return (-1);
  return (0);
}

void	del_sem(int sem_id)
{
  semctl(sem_id, 0, IPC_RMID);
}
