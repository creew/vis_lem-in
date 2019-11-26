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

	ft_bzero((void *)&max_xy, sizeof(max_xy));
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
					min_xy->x = ft_min(room->x, min_xy->x);
					max_xy.x = ft_max(room->x, max_xy.x);
					min_xy->y = ft_min(room->y, min_xy->y);
					max_xy.y = ft_max(room->y, max_xy.y);
				}
			}
			wh->x = ft_abs(max_xy.x - min_xy->x) + 1;
			wh->y = ft_abs(max_xy.y - min_xy->y) + 1;
		}
}

static void		rebase_rooms_xy(t_lemin *lem, t_point *min)
{
	size_t		index;
	t_roomdata	*rdata;

	index = -1;
	while (ft_array_get(&lem->rooms, ++index, (void **)&rdata) == 0)
	{
		rdata->x -= min->x;
		rdata->y -= min->y;
	}
}

void			recalc_room_size(t_vis *vis, int w, int h)
{
	float		hscale;
	float		wscale;
	t_point		wh;
	t_point		min;
	SDL_Rect	main;

	vis->wwidth = w;
	vis->wheight = h;
	get_xy_size(&vis->lem, &wh, &min);
	get_main_rect(&main, w, h);
	wscale = (float)main.w / (float)(wh.x);
	hscale = (float)main.h / (float)(wh.y);
	vis->roomsize = wscale < hscale ? wscale : hscale;
	rebase_rooms_xy(&vis->lem, &min);
}
