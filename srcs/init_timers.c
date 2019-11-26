/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_timers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:22:02 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/20 11:22:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static Uint32	anim_tim_callback(Uint32 interval, void *param)
{
	t_vis	*vis;

	vis = (t_vis *)param;
	if (!vis->paused)
		vis->tim_count++;
	return (interval);
}

SDL_TimerID		add_anim_timer(t_vis *vis)
{
	return (SDL_AddTimer(20, anim_tim_callback, vis));
}

Uint32			moves_tim_callback(Uint32 interval, void *param)
{
	t_vis			*vis;
	SDL_Event		event;
	SDL_UserEvent	userevent;

	vis = (t_vis *)param;
	userevent.code = vis->moves_count == 0 ? 0 : 1;
	userevent.type = SDL_USEREVENT;
	userevent.data1 = NULL;
	userevent.data2 = (void *)vis->moves_count;
	event.type = SDL_USEREVENT;
	event.user = userevent;
	SDL_PushEvent(&event);
	if (!vis->paused)
		vis->moves_count += vis->speed;
	if (vis->moves_count >= MOVE_STEPS)
	{
		vis->moves_count = 0;
		userevent.code = 2;
		userevent.data2 = (void *)vis->moves_count;
		event.type = SDL_USEREVENT;
		event.user = userevent;
		SDL_PushEvent(&event);
	}
	return (interval);
}

SDL_TimerID		add_moves_timer(void *param)
{
	return (SDL_AddTimer(1, moves_tim_callback, param));
}
