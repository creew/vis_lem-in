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

#include "process_events.h"
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
			lemdata->src_room = vis->lem.se.start;
		else
			lemdata->src_room = lemdata->dst_room;
		lemdata->dst_room = rdata;
		lemdata->angle = atan2f(lemdata->dst_room->y - lemdata->src_room->y,
			lemdata->dst_room->x - lemdata->src_room->x) * 180 / M_PI + 90;
		lemdata->shift = rand() % 255;
		lemdata->move = 1;
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

static t_result	do_move(t_vis *vis)
{

	return (RET_OK);
}

static void		set_move(void *data)
{
	t_lemdata	*ldata;

	ldata = (t_lemdata *)data;
	if (ldata->dst_room->cmd == LEM_CMD_END)
		ldata->move = 2;
}

static t_result	finish_move(t_vis *vis)
{
	ft_array_foreach(&vis->curlems, set_move);
	vis->curlems.num_elems = 0;
	return (RET_OK);
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
				do_move(vis);
			else if (e.user.code == 2)
				finish_move(vis);
		}
	}
	return (run);
}