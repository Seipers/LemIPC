/*
** lemipc.h for lemipc in /home/sebastien/Rendu/PSU_2016_lemipc/include
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Tue Mar 21 03:51:48 2017 Sebastien Le Guischer
** Last update Sun Apr  2 20:29:08 2017 Sebastien Le Guischer
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# include <sys/types.h>

/*
** CONFIG
*/

# define ADD "Add - "
# define DEL "Delete - "
# define OK "Ok"
# define T_START "Your turn"
# define DESTROY "Destroy"
# define T_END "End turn"
# define WIN "Win"
# define QUIT "Quit"

typedef struct	s_info
{
  int		width;
  int		height;
  int		shm_id;
  int		sem_id;
  int		msg_id;
  key_t		key;
  char		*bin;
}		t_info;

typedef struct	s_msg
{
  int		msg_s;
  char		msg[35];
}		t_msg;

int		set_default_sem(t_info *info);
int		set_default_shm(t_info *info);
void		del_shm(int shm_id);
void		del_msg(int msg_id);
void		del_sem(int sem_id);
void		send_msg(int msg_id, char *str);
int		wait_str(int msg_id, char *str);

/*
** PLAYER
*/

typedef struct	s_player
{
  int		team;
  int		pid;
  int		msg_id;
}		t_player;

typedef struct		s_list_player
{
  t_player		*player;
  struct s_list_player	*next;
}			t_list_player;

t_list_player	*add_player_list(t_list_player *list, t_player *player);
t_list_player	*roll_player_list(t_list_player *list);
t_player	*rem_player_list(t_list_player **list, int pid);

/*
** IA
*/

int		user(t_info *info, int team);
void		ia(t_info *i, int m[2], int team, int pos);
int		use_sem(int pos, int sem_id);
int		leave_sem(int pos, int sem_id);
int		use_shm(int pos, int shm_id, int team);
int		leave_shm(int pos, int shm_id);
int		move_player(t_info *i, int *map, int pos, int e);
int		check_map(t_info *i, int *m, int sq[2][2], int team);
int		find_enemy(t_info *i, int *map, int team, int pos);
int		search_team(t_info *info, int *map, int team, int pos);
void		check_destroy(t_info *info, int *map, int pos, int team);
void		get_position(t_info *info, int pos, int *i, int *j);

/*
** TEAM
*/

typedef struct		s_list_team
{
  int			num;
  int			nb;
  t_list_player		*players;
  struct s_list_team	*next;
}			t_list_team;

t_list_team	*add_team_list(t_list_team *list, t_player *player);
t_list_team	*rem_team_list(t_list_team *list,
			       int pid, int team, t_info *info);
void		print_list(t_list_team *list);

/*
** REFEREE
*/

typedef struct	s_referee
{
  int		start;
  int		nb_team;
  int		p_max;
  t_list_team	*teams;
  t_list_player	*players;
}		t_referee;

void		referee(t_info *info);
void		add_player(char *msg, t_referee *ref, t_info *info);
void		delete_player(char *msg, t_referee *ref, t_info *info);
void		delete_last_player(t_referee *ref, t_info *info,
			   int team_id, int pid);
void		update_team_info(t_referee *ref);

/*
** MAP
*/

void		print_map(t_info *info, t_referee ref);

#endif /* !LEMIPC_H_ */
