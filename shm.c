/*
** sem.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 11:34:20 2017 Sebastien Le Guischer
** Last update Fri Mar 31 23:17:36 2017 Dorian Voravong
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "lemipc.h"

int	set_default_shm(t_info *info)
{
  int	i;
  void	*addr;
  int	*state;

  i = 0;
  if ((addr = shmat(info->shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (-1);
  state = (int *)addr;
  while (i < info->width * info->height)
    {
      state[i] = -1;
      i++;
    }
  return (0);
}

int	use_shm(int pos, int shm_id, int team)
{
  void	*addr;
  int	*state;

  if ((addr = shmat(shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (-1);
  state = (int *)addr;
  state[pos] = team;
  return (0);
}

int	leave_shm(int pos, int shm_id)
{
  void	*addr;
  int	*state;

  if ((addr = shmat(shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (-1);
  state = (int *)addr;
  state[pos] = -1;
  return (0);
}

void	del_shm(int shm_id)
{
  shmctl(shm_id, IPC_RMID, NULL);
}
