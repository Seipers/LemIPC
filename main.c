/*
** main.c for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 01:54:34 2017 Sebastien Le Guischer
** Last update Sun Apr  2 17:12:11 2017 Dorian Voravong
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <time.h>
#include "lemipc.h"

int	is_nb(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] < '0' || str[i] > '9')
	exit(1);
      i++;
    }
  return (atoi(str));
}

int	get_last_info(t_info *info)
{
  if ((info->shm_id = shmget(info->key, 0, SHM_W | SHM_R)) != -1)
    {
      if ((info->sem_id = semget(info->key, 0, SHM_R | SHM_W)) == -1
	  || (info->msg_id = msgget(info->key, SHM_W | SHM_R)) == -1)
	return (-1);
      return (0);
    }
  else
    {
      if ((info->shm_id = shmget(info->key,
				 info->width * info->height * sizeof(int),
				 IPC_CREAT | SHM_W | SHM_R)) == -1
	  || (info->sem_id = semget(info->key,
				    info->width * info->height,
				    IPC_CREAT | SHM_R | SHM_W)) == -1
	  || (info->msg_id = msgget(info->key,
				    IPC_CREAT | SHM_W | SHM_R)) == -1)
	return (-1);
      if (set_default_sem(info) == -1 || set_default_shm(info) == -1)
	return (-1);
      return (1);
    }
}

int	set_info(int ac, char **av, t_info *info)
{
  if (ac != 3)
    return (1);
  srand(getpid() * time(NULL));
  if ((info->key = ftok(av[1], -1)) == -1)
    return (1);
  info->bin = av[1];
  info->width = 10;
  info->height = 10;
  return (0);
}

int		main(int ac, char **av)
{
  t_info	info;
  int		ret;
  pid_t		pid;

  pid = 1;
  if (set_info(ac, av, &info))
    return (1);
  if ((ret = get_last_info(&info)) == -1)
    return (1);
  else if (ret == 1)
    if ((pid = fork()) == -1)
      return (1);
  if (pid == 0)
    referee(&info);
  else
    {
      if (user(&info, is_nb(av[2])) == -1)
	return (1);
      wait(&ret);
    }
  return (0);
}
