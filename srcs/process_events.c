/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:01:22 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/20 11:01:23 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"
#include <math.h>

static  t_result	process_move(t_vis *vis, char *str)
{
	char		*s;
	int 		index;
	char		*end;
	int			last;
	t_roomdata	*rdata;
	t_lemdata	*lemdata;

	last = 0;
	while (!last && (s = get_next_word(str, &last)))
	{
		if (*s++ != 'L')
			return (ERR_NOT_MOVE);
		index = (int) ft_strtol(s, &end, 10);
		if (index < 1 || index > vis->lem.num_ants)
			return (ERR_NOT_MOVE);
		if (*end++ != '-')
			return (ERR_NOT_MOVE);
		if ((rdata = find_room_by_name(&vis->lem.rooms, end)) == NULL)
			return (ERR_NOT_MOVE);
		str = s + ft_strlen(s) + 1;
		lemdata = &vis->lemarr[index - 1];
		if (lemdata->move == 0)
		{
			lemdata->src_room = vis->lem.se.start;
			lemdata->shift = rand() % 255;
		}
		else
			lemdata->src_room = lemdata->dst_room;
		lemdata->dst_room = rdata;
		lemdata->angle = atan2f(lemdata->dst_room->y - lemdata->src_room->y,
			lemdata->dst_room->x - lemdata->src_room->x) * 180 / M_PI + 90;
		lemdata->move = 1;
		lemdata->x = lemdata->src_room->x * vis->roomsize;
		lemdata->y = lemdata->src_room->y * vis->roomsize;
		ft_array_add(&vis->curlems, lemdata);
	}
	return (RET_OK);
}

static t_result	init_move(t_vis *vis)
{
	int			res;
	char		*s;
	t_result	ret;

	res = get_next_line(vis->lem.fd, &s);
	if (res < 0)
		return (ERR_GNL_ERROR);
	if (res > 0)
	{
		if ((ret = process_move(vis, s)) != RET_OK)
			return (ret);
		ft_strdel(&s);
	}
	return (RET_OK);
}

static t_result	do_move(t_vis *vis, size_t count)
{
	size_t		size;
	t_lemdata	*ldata;
	t_fpoint	src;
	t_fpoint	dst;

	size = ft_array_size(&vis->curlems);
	while (size--)
	{
		if (ft_array_get(&vis->curlems, size, (void **)&ldata) == 0)
		{
			dst.x = (float)ldata->dst_room->x * vis->roomsize;
			dst.y = (float)ldata->dst_room->y * vis->roomsize;
			src.x = (float)ldata->src_room->x * vis->roomsize;
			src.y = (float)ldata->src_room->y * vis->roomsize;
			ldata->x = src.x + (dst.x - src.x) * count / MOVE_STEPS;
			ldata->y = src.y + (dst.y - src.y) * count / MOVE_STEPS;
		}
	}
	return (RET_OK);
}

static void		set_move(void *data, void *udata)
{
	t_lemdata	*ldata;

	(void)udata;
	ldata = (t_lemdata *)data;
	if (ldata->dst_room->cmd == LEM_CMD_END)
		ldata->move = 2;
}

static t_result	finish_move(t_vis *vis)
{
	ft_array_foreach(&vis->curlems, set_move, NULL);
	vis->curlems.num_elems = 0;
	return (RET_OK);
}

int				get_index_handle(int x, int y, t_vis *vis)
{
	int		size;
	t_rect	rect;
	SDL_Point	point;
	point.x = x;
	point.y = y;

	size = vis->buttonsimg.nframes;
	while (size--)
	{
		get_handle_rect(&rect, size, vis->wwidth, vis->wheight);
		if (SDL_PointInRect(&point, &rect))
			return (size);
	}
	return (-1);
}

void			handle_mouse(SDL_Event *e, SDL_Window *window, t_vis *vis)
{
	int		index;

	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if ((index = get_index_handle(e->button.x, e->button.y, vis)) != -1)
		{
			if (index == 0)
			{


			}
			else if (index == 1)
			{
				if (vis->paused)
					vis->paused = 0;
			}
			else if (index == 2)
			{
				SDL_RemoveTimer(vis->moves_tim);
				vis->moves_count = 0;
			}
			else if (index == 3)
			{
				vis->paused = !vis->paused;
			}
			else if (index == 4)
			{

			}
		}
	}
}

int				process_event(t_vis *vis)
{
	int			run;
	SDL_Event	e;

	run = 1;
	while(SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			run = 0;
		else if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				recalc_room_size(vis, e.window.data1, e.window.data2);
		}
		else if (e.type == SDL_USEREVENT)
		{
			if (e.user.code == 0)
				init_move(vis);
			else if (e.user.code == 1)
				do_move(vis, (size_t)e.user.data2);
			else if (e.user.code == 2)
				finish_move(vis);
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			handle_mouse(&e, vis->window, vis);
		}

	}
	return (run);
}