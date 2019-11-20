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

int		process_event(t_vis *vis)
{
	int			run;
	SDL_Event	e;

	run = 1;
	while(SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			run = 0;
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				recalc_room_size(vis, e.window.data1, e.window.data2);
		}
	}
	return (run);
}