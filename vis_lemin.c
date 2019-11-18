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
#include <fcntl.h>

static int		sdl_destroy(t_vis *vis)
{
	SDL_RemoveTimer(vis->timer);
	vis->timer = 0;
	SDL_DestroyWindow(vis->window);
	vis->window = NULL;
	SDL_DestroyRenderer(vis->ren);
	vis->ren = NULL;
	SDL_DestroyTexture(vis->ants);
	vis->ants = NULL;
	SDL_DestroyTexture(vis->font_text);
	vis->font_text = NULL;
	TTF_CloseFont(vis->font);
	vis->font = 0;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	return (1);
}

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
	int		*count;

	count = (int *)param;
	*count = *count + 1;
	return (interval);
}

void		init_lem(t_lemin *lem)
{
	ft_bzero(lem, sizeof(*lem));
	ft_array_init(&lem->rooms, 128);
	ft_array_init(&lem->links, 128);
	ft_array_init(&lem->paths, 128);
}

int		main(int ac, char *av[])
{
	t_vis			vis;
	int 			run;
	SDL_Event		e;
	SDL_Rect 		srcrect;
	SDL_Rect 		dstrect;
	SDL_Color		color;
	SDL_Point		text_point;
	int 			fd;

	ft_bzero(&vis, sizeof(vis));
	vis.wheight = 1000;
	vis.wwidth = 1000;
	vis.window = NULL;
	vis.tim_count = 0;

	init_lem(&vis.lem);
	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
		fd = 0;
	read_file(&vis, fd);
	if (sdl_init(&vis) != 0)
		return (sdl_destroy(&vis));
	if (load_image(&vis) != 0)
		return (sdl_destroy(&vis));
	if (load_font(&vis) != 0)
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
		dstrect.h = 440;
		dstrect.w = 400;

		text_point.x = 10;
		text_point.y = 10;

		color.a = 255;
		color.r = 0;
		color.g = 0;
		color.b = 0;

		SDL_RenderClear(vis.ren);
		text_out(&vis, &text_point,"Привет муравьям!", color);
		SDL_RenderCopyEx(vis.ren, vis.ants, &srcrect, &dstrect, 0, NULL , SDL_FLIP_NONE);
		SDL_RenderPresent(vis.ren);
	}
	sdl_destroy(&vis);
	return (0);
}
