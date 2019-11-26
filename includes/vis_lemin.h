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

typedef unsigned char	t_uchar;
typedef int				t_result;
typedef t_ftarray		t_roomarr;
typedef t_ftarray		t_linkarr;
typedef t_ftarray		t_patharr;
typedef t_ftarray		t_lemsarr;

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
# define ERR_EMPTY_STR				(-19)
# define ERR_NOT_MOVE				(-20)

# define LEM_CMD_NONE			(0)
# define LEM_CMD_START			(1)
# define LEM_CMD_END			(2)
# define LEM_CMD_UNKNOWN		(3)

# define MOVE_STEPS				(5000)

# define ANTS_IMG		"./resources/all_ants.png"
# define PLAY_PAUSE_IMG	"./resources/play_pause.png"
# define NES_FONT		"./resources/nes.ttf"

typedef struct	s_fatline
{
	SDL_Texture		*texture;
	SDL_Rect		src;
	SDL_Rect		dst;
	SDL_Point		center;
	float			angle;
}				t_fatline;

typedef struct	s_img
{
	SDL_Texture		*texture;
	int				w;
	int				h;
	int				nframes;
}				t_img;

typedef SDL_Rect	t_rect;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_fpointxy
{
	float	x;
	float	y;
}				t_fpointxy;

typedef struct	s_roomdata
{
	size_t		index;
	int			x;
	int			y;
	char		cmd;
	char		name[1];
}				t_roomdata;

typedef struct	s_lemdata
{
	t_roomdata	*src_room;
	t_roomdata	*dst_room;
	t_uchar		shift;
	t_uchar		move;
	float		angle;
	float		x;
	float		y;
}				t_lemdata;

typedef struct	s_linkdata
{
	t_roomdata	*left;
	t_roomdata	*right;
}				t_linkdata;

typedef struct	s_borders
{
	t_roomdata	*start;
	t_roomdata	*end;
}				t_borders;

typedef struct	s_lemin
{
	int			num_ants;
	int			fd;
	t_roomarr	rooms;
	t_linkarr	links;
	t_patharr	paths;
	t_borders	se;
}				t_lemin;

typedef struct	s_vis
{
	t_lemin			lem;
	int				wwidth;
	int				wheight;
	float			roomsize;
	t_lemdata		*lemarr;
	t_lemsarr		curlems;

	size_t			tim_count;
	size_t			moves_count;
	int				paused;
	int				speed;
	int				at_start;
	int				finished;
	t_img			antsimg;
	t_img			buttonsimg;
	SDL_Window		*window;
	SDL_Renderer	*ren;

	SDL_Texture		*font_text;
	SDL_TimerID		anim_tim;
	SDL_TimerID		moves_tim;
	TTF_Font		*font;
	TTF_Font		*info_font;
}				t_vis;

void			print_sdl_error(const char *err);

int				sdl_init(t_vis *vis);
int				load_image_ants(t_vis *vis);
int				load_image_buttons(t_vis *vis);
TTF_Font		*load_font(int pt_size);
void			text_out(t_vis *vis, SDL_Rect *rect, char *txt,
					SDL_Color color);
void			info_text_out(t_vis *vis, SDL_Point *point, char *txt,
					SDL_Color color);
int				read_file(t_vis *vis);
int				count_numbers(char *str);
char			*get_next_word(char *str, int *last);
t_result		add_lem_link(t_roomarr *rooms, t_linkarr *links, char *str);
t_result		add_lem_room(t_roomarr *rooms, char *str, int cmd);
t_roomdata		*find_room_by_name(t_roomarr *rooms, const char *name);
t_result		check_all(t_lemin *lem);
void			recalc_room_size(t_vis *vis, int w, int h);

void			draw_links(t_vis *vis);
void			draw_rooms(t_vis *vis);
void			draw_ants(t_vis *vis);
void			draw_handles(t_vis *vis);

SDL_TimerID		add_anim_timer(t_vis *vis);
SDL_TimerID		add_moves_timer(void *param);

int				vis_destroy(t_vis *vis, int is_err);

void			draw_all(t_vis *vis);

int				process_event(t_vis *vis);

void			get_main_rect(SDL_Rect *rect, int ww, int wh);
void			get_handles_rect(SDL_Rect *rect, int ww, int wh);
void			get_handle_rect(SDL_Rect *rect, int index, int ww, int wh);
void			get_info_rect(SDL_Rect *rect, int ww, int wh);

void			draw_arc(SDL_Renderer *ren, SDL_Point c, int q, int r);
void			draw_round_rect(SDL_Renderer *ren, SDL_Rect *rect, int r);
void			draw_line(SDL_Renderer *ren, SDL_Point *start, SDL_Point *end,
					int th);
void			draw_filled_round_rect(SDL_Renderer *ren, SDL_Rect *rect,
					int r);

t_result		init_move(t_vis *vis);
t_result		finish_move(t_vis *vis);
t_result		do_move(t_vis *vis, size_t count);
SDL_Color		get_color(int r, int g, int b, int a);
#endif
