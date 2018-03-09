/*
** tekpixel.c for lemipc in /home/dorian.voravong/rendu/PSU_2016_lemipc/bonus
** 
** Made by Dorian Voravong
** Login   <dorian.voravong@epitech.net>
** 
** Started on  Sun Apr  2 19:09:03 2017 Dorian Voravong
** Last update Sun Apr  2 19:16:47 2017 Dorian Voravong
*/

#include "lapin.h"

void		tekpixel(t_bunny_pixelarray *pix,
			 t_bunny_position *pos,
			 unsigned int color)
{
  unsigned int	*pixel;

  pixel = pix->pixels;
  if ((pos->x < pix->clipable.clip_width
       && pos->y < pix->clipable.clip_height)
      && pos->x >= 0 && pos->y >= 0)
    pixel[pix->clipable.clip_width * pos->y + pos->x] = color;
}

void			teksquare(t_bunny_pixelarray *pix,
				  t_bunny_position *pos,
				  unsigned int color,
				  int size)
{
  t_bunny_position	pos2;

  pos2.y = pos->y;
  while (pos2.y < pos->y + size)
    {
      pos2.x = pos->x;
      while (pos2.x < pos->x + size)
	{
	  tekpixel(pix, &pos2, color);
	  pos2.x++;
	}
      pos2.y++;
    }
}
