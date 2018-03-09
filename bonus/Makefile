##
## Makefile for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc
## 
## Made by Sebastien Le Guischer
## Login   <sebastien@epitech.net>
## 
## Started on  Tue Mar 21 01:50:46 2017 Sebastien Le Guischer
## Last update Sun Apr  2 19:13:22 2017 Dorian Voravong
##

NAME		= lemipc

SRCS		= main.c\
		  player.c\
		  ia.c\
		  move.c\
		  destroy.c\
		  map.c\
		  check_map.c\
		  sem.c\
		  shm.c\
		  msg.c\
		  team.c\
		  referee.c\
		  team_list.c\
		  user.c\
		  player_list.c\
		  tekpixel.c

LIB		= -I/home/${USER}/.froot/include\
		  -L/home/${USER}/.froot/lib -llapin -lsfml-audio -lsfml-graphics\
		  -lsfml-window -lsfml-system -lstdc++ -ldl -lm


OBJS		= $(SRCS:.c=.o)

CFLAGS		= -W -Wall -Wextra -Iinclude -fno-stack-protector

GCC		= gcc

RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	$(GCC) -o $(NAME) $(OBJS) $(LIB) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
