/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:08:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/20 11:08:20 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static void		get_xy_size(t_lemin *lem, t_point *wh, t_point *min_xy)
{
	t_point		max_xy;
	size_t		size;
	t_roomdata	*room;

	ft_bzero((void *) &max_xy, sizeof(max_xy));
	if ((size = ft_array_size(&lem->rooms)))
		if (ft_array_get(&lem->rooms, --size, (void **)&room) == 0)
		{
			min_xy->x = room->x;
			max_xy.x = room->x;
			min_xy->y = room->y;
			max_xy.y = room->y;
			while (size--)
			{
				if (ft_array_get(&lem->rooms, size, (void **)&room) == 0)
				{
					min_xy->x = room->x < min_xy->x ? room->x : min_xy->x;
					max_xy.x = room->x > max_xy.x ? room->x : max_xy.x;
					min_xy->y = room->y < min_xy->y ? room->y : min_xy->y;
					max_xy.y = room->y > max_xy.y ? room->y : max_xy.y;
				}
			}
			wh->x = abs(max_xy.x - min_xy->x) + 1;
			wh->y = abs(max_xy.y - min_xy->y) + 1;
		}
}

static void		rebase_rooms_xy(t_lemin *lem, t_point *min)
{
	size_t		size;
	t_roomdata	*rdata;

	size = ft_array_size(&lem->rooms);
	while (size--)
	{
		if (ft_array_get(&lem->rooms, size, (void **)&rdata) == 0)
		{
			rdata->x -= min->x;
			rdata->y -= min->y;
		}
	}
}

void			recalc_room_size(t_vis *vis, int w, int h)
{
	float		hscale;
	float		wscale;
	t_point		wh;
	t_point		min;

	vis->wwidth = w;
	vis->wheight = h;
	get_xy_size(&vis->lem, &wh, &min);
	wscale = 1.0 * vis->wwidth / (wh.x);
	hscale = 1.0 * vis->wheight / (wh.y);
	vis->roomsize = wscale < hscale ? wscale : hscale;
	rebase_rooms_xy(&vis->lem, &min);
	vis->antscale = 500 / vis->roomsize;
}