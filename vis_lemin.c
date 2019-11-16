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

static void		sdl_destroy(t_vis *vis)
{
	SDL_DestroyWindow(vis->window);
	SDL_Quit();
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
		return (1);
	if (load_image(&vis) != 0)
		return (1);
	vis.timer = SDL_AddTimer(50, my_callbackfunc, &(vis.tim_count));
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

		SDL_RenderClear(vis.ren);
		SDL_RenderCopy(vis.ren, vis.ants, &srcrect, NULL);
		SDL_RenderPresent(vis.ren);
	}
	SDL_Delay(2000);
	sdl_destroy(&vis);
	ft_putendl("Hello World!");
	return (0);
}
