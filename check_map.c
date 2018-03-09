/*
** check_map.c for lemipc in /home/dorian.voravong/rendu/PSU_2016_lemipc
** 
** Made by Dorian Voravong
** Login   <dorian.voravong@epitech.net>
** 
** Started on  Sat Apr  1 02:24:46 2017 Dorian Voravong
** Last update Sun Apr  2 17:16:52 2017 Dorian Voravong
*/

#include "lemipc.h"

int	check_map2(t_info *in, int *map, int square[2][2], int team)
{
  int	i;
  int	j;

  i = square[1][0];
  j = square[1][1];
  while (j != square[0][1])
    {
      if (i >= 0 && j >= 0 && i < in->height && j < in->width)
	{
	  if (map[i * in->width + j] != -1 && map[i * in->width + j] != team)
	    return (i * in->width + j);
	}
      j--;
    }
  while (i != square[0][0])
    {
      if (i >= 0 && j >= 0 && i < in->height && j < in->width)
	{
	  if (map[i * in->width + j] != -1 && map[i * in->width + j] != team)
	    return (i * in->width + j);
	}
      i--;
    }
  return (-1);
}

int	check_map(t_info *in, int *map, int square[2][2], int team)
{
  int	i;
  int	j;

  i = square[0][0];
  j = square[0][1];
  while (j != square[1][1])
    {
      if (i >= 0 && j >= 0 && i < in->height && j < in->width)
	{
	  if (map[i * in->width + j] != -1 && map[i * in->width + j] != team)
	    return (i * in->width + j);
	}
      j++;
    }
  while (i != square[1][0])
    {
      if (i >= 0 && j >= 0 && i < in->height && j < in->width)
	{
	  if (map[i * in->width + j] != -1 && map[i * in->width + j] != team)
	    return (i * in->width + j);
	}
      i++;
    }
  return (check_map2(in, map, square, team));
}
