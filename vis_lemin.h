/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_lemin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:33:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 10:33:52 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_LEMIN_H
# define VIS_LEMIN_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include "libft.h"

typedef	int			t_result;
typedef t_ftarray	t_roomarr;
typedef t_ftarray	t_linkarr;
typedef t_ftarray	t_patharr;
typedef t_ftarray	t_path;

# define RET_OK						(0)
# define ERR_READ_ANTS_NUMBER		(-1)
# define ERR_WRONG_ANTS_NUMBER		(-2)
# define ERR_GNL_ERROR				(-3)
# define ERR_ENOMEM					(-4)
# define ERR_WRONG_ROOM_NAME		(-5)
# define ERR_WRONG_ROOM_ARG			(-6)
# define ERR_WRONG_LINK				(-7)
# define ERR_WRONG_LINK_ROOM		(-8)
# define ERR_ROOM_NAME_DUPL 		(-9)
# define ERR_EMPTY_ROOM_NAME		(-10)
# define ERR_WRONG_LINK_TO_LINK		(-11)
# define ERR_NO_START_OR_END 		(-12)
# define ERR_LINK_DUPL 				(-13)
# define ERR_ROOM_XY_DUPL			(-14)
# define ERR_NO_LINKS				(-15)
# define ERR_NO_PATH				(-16)
# define ERR_INCORRECT_PATH_REMOVE	(-17)
# define ERR_CMD_NOT_FOUNDED		(-18)

# define LEM_CMD_NONE			(0)
# define LEM_CMD_START			(1)
# define LEM_CMD_END			(2)
# define LEM_CMD_UNKNOWN		(3)

typedef struct	s_antsimg {
	int		w;
	int 	h;
	int 	nframes;
}				t_antsimg;

typedef struct	s_point
{
	int		x;
	int 	y;
}				t_point;

typedef struct	s_roomdata
{
	size_t		index;
	int			x;
	int			y;
	int 		weigth;
	char		cmd;
	char 		visited;
	char 		meh_visit;
	int			ant_index;
	int 		ant_count;
	char		name[1];
}				t_roomdata;

typedef struct	s_linkdata
{
	t_roomdata	*left;
	t_roomdata	*right;
}				t_linkdata;

typedef	struct	s_borders
{
	t_roomdata	*start;
	t_roomdata	*end;
}				t_borders;

typedef struct	s_lemin
{
	int			num_ants;
	t_roomarr	rooms;
	t_linkarr	links;
	t_patharr	paths;
	t_borders	se;
}				t_lemin;

typedef struct	s_vis {
	t_lemin			lem;
	int				wwidth;
	int 			wheight;
	double			roomsize;
	double			antscale;

	size_t			tim_count;
	t_antsimg		antsimg;
	SDL_Window		*window;
	SDL_Renderer	*ren;
	SDL_Texture		*ants;
	SDL_Texture		*font_text;
	SDL_TimerID		timer;
	TTF_Font		*font;
}				t_vis;

void		print_sdl_error(const char *err);

int			sdl_init(t_vis *vis);
int 		load_image(t_vis *vis);
int			load_font(t_vis *vis);
void		text_out(t_vis *vis, SDL_Point *point, char *txt, SDL_Color color);

int			read_file(t_vis *vis, int fd);
int			count_numbers(char *str);
char		*get_next_word(char *str, int *last);
t_result	add_lem_link(t_lemin *lem, char *str);
t_result	add_lem_room(t_lemin *lem, char *str, int cmd);
t_roomdata	*find_room_by_name(t_roomarr *rooms, const char *name);
#endif
