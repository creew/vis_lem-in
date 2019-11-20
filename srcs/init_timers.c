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
	int		*count;

	count = (int *)param;
	*count = *count + 1;
	return (interval);
}

SDL_TimerID		add_anim_timer(void *param)
{
	return (SDL_AddTimer(20, anim_tim_callback, param));
}

Uint32			moves_tim_callback(Uint32 interval, void *param)
{
	int		*count;

	count = (int *)param;
	*count = *count + 1;
	return (interval);
}

SDL_TimerID		add_moves_timer(void *param)
{
	return (SDL_AddTimer(1, moves_tim_callback, param));
}
