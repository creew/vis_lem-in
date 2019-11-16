/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_lemin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:33:38 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 10:33:39 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static int		sdl_destroy(t_vis *vis)
{
	SDL_DestroyWindow(vis->window);
	vis->window = NULL;
	SDL_DestroyRenderer(vis->ren);
	vis->ren = NULL;
	SDL_DestroyTexture(vis->ants);
	vis->ants = NULL;
	SDL_RemoveTimer(vis->timer);
	vis->timer = 0;
	SDL_Quit();
	IMG_Quit();
	return (1);
}

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
	int		*count;

	count = (int *)param;
	*count = *count + 1;
	return (interval);
}

int		main(int ac, char *av[])
{
	t_vis			vis;
	int 			run;
	SDL_Event		e;
	SDL_Rect 		srcrect;
	SDL_Rect 		dstrect;

	(void)ac;
	(void)av;
	vis.wheight = 1000;
	vis.wwidth = 1000;
	vis.window = NULL;
	vis.tim_count = 0;

	if (sdl_init(&vis) != 0)
		return (sdl_destroy(&vis));
	if (load_image(&vis) != 0)
		return (sdl_destroy(&vis));
	vis.timer = SDL_AddTimer(20, my_callbackfunc, &(vis.tim_count));
	run = 1;
	while (run) {
		while(SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				run = 0;
			}
		}
		srcrect.x = 0 + (vis.tim_count % vis.antsimg.nframes) *
			(vis.antsimg.w / vis.antsimg.nframes);
		srcrect.y = 0;
		srcrect.w = (vis.antsimg.w / vis.antsimg.nframes);
		srcrect.h = vis.antsimg.h;

		dstrect.x = 300;
		dstrect.y = 300;
		dstrect.h = 220;
		dstrect.w = 200;

		SDL_RenderClear(vis.ren);
		SDL_RenderCopyEx(vis.ren, vis.ants, &srcrect, &dstrect, vis.tim_count % 360, NULL , SDL_FLIP_NONE);
		SDL_RenderPresent(vis.ren);
	}
	sdl_destroy(&vis);
	return (0);
}
