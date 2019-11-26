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

int			get_index_handle(int x, int y, t_vis *vis)
{
	int			size;
	t_rect		rect;
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

void		handle_mouse(SDL_Event *e, t_vis *vis)
{
	int		index;

	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if ((index = get_index_handle(e->button.x, e->button.y, vis)) != -1)
		{
			if (index == 0)
			{
				if (vis->speed > 1)
					vis->speed--;
			}
			else if (index == 1)
				vis->paused = !vis->paused;
			else if (index == 2)
			{
				if (vis->speed < 9)
					vis->speed++;
			}
		}
	}
}

static void	process_user_events(t_vis *vis, SDL_Event *e)
{
	if (e->user.code == 0)
		init_move(vis);
	else if (e->user.code == 1)
		do_move(vis, (size_t)e->user.data2);
	else if (e->user.code == 2)
		finish_move(vis);
}

int			process_event(t_vis *vis)
{
	int			run;
	SDL_Event	e;

	run = 1;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			run = 0;
		else if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				recalc_room_size(vis, e.window.data1, e.window.data2);
		}
		else if (e.type == SDL_USEREVENT)
			process_user_events(vis, &e);
		else if (e.type == SDL_MOUSEBUTTONUP)
			handle_mouse(&e, vis);
	}
	return (run);
}
