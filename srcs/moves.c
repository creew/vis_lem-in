/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:24:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/26 16:24:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static void			add_lem_to_curlems(t_vis *vis, t_lemdata *lemdata,
	t_roomdata *rdata)
{
	if (lemdata->move == 0)
	{
		vis->at_start--;
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

static t_result		process_move(t_vis *vis, char *str)
{
	char		*s;
	int			index;
	char		*end;
	int			last;
	t_roomdata	*rdata;

	last = 0;
	while (!last && (s = get_next_word(str, &last)))
	{
		if (*s++ != 'L')
			return (ERR_NOT_MOVE);
		index = (int)ft_strtol(s, &end, 10);
		if (index < 1 || index > vis->lem.num_ants)
			return (ERR_NOT_MOVE);
		if (*end++ != '-')
			return (ERR_NOT_MOVE);
		if ((rdata = find_room_by_name(&vis->lem.rooms, end)) == NULL)
			return (ERR_NOT_MOVE);
		str = s + ft_strlen(s) + 1;
		add_lem_to_curlems(vis, &vis->lemarr[index - 1], rdata);
	}
	return (RET_OK);
}

t_result			init_move(t_vis *vis)
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

t_result			do_move(t_vis *vis, size_t count)
{
	size_t		index;
	t_lemdata	*ldata;
	t_fpointxy	src;
	t_fpointxy	dst;

	index = -1;
	while (ft_array_get(&vis->curlems, ++index, (void **)&ldata) == 0)
	{
		dst.x = (float)ldata->dst_room->x * vis->roomsize;
		dst.y = (float)ldata->dst_room->y * vis->roomsize;
		src.x = (float)ldata->src_room->x * vis->roomsize;
		src.y = (float)ldata->src_room->y * vis->roomsize;
		ldata->x = src.x + (dst.x - src.x) * count / MOVE_STEPS;
		ldata->y = src.y + (dst.y - src.y) * count / MOVE_STEPS;
	}
	return (RET_OK);
}

t_result			finish_move(t_vis *vis)
{
	size_t		index;
	t_lemdata	*ldata;

	index = -1;
	while (ft_array_get(&vis->curlems, ++index, (void **)&ldata) == 0)
	{
		if (ldata->dst_room->cmd == LEM_CMD_END)
		{
			ldata->move = 2;
			vis->finished++;
		}
	}
	vis->curlems.num_elems = 0;
	return (RET_OK);
}
