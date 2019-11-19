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

int 	get_window_size(SDL_Renderer *ren, int *w, int *h)
{
	if (SDL_GetRendererOutputSize(ren, w, h) != 0)
	{
		SDL_Log("SDL_GetRendererOutputSize failed: %s", SDL_GetError());
		return 1;
	}
	return (0);
}

void 	get_xy_size(t_lemin *lem, t_point *wh, t_point *min_xy)
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

void	rebase_rooms_xy(t_lemin *lem, t_point *min)
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

void 	recalc_room_size(t_vis *vis, int w, int h)
{
	double	hscale;
	double	wscale;
	t_point	wh;
	t_point	min;

	vis->wwidth = w;
	vis->wheight = h;
	get_xy_size(&vis->lem, &wh, &min);
	wscale = 1.0 * vis->wwidth / (wh.x);
	hscale = 1.0 * vis->wheight / (wh.y);
	vis->roomsize = wscale < hscale ? wscale : hscale;
	rebase_rooms_xy(&vis->lem, &min);
	vis->antscale = 500 / vis->roomsize;
}

void	draw_links(t_vis *vis)
{
	size_t		size;
	t_linkdata	*link;
	t_point		start;
	t_point		end;
	double 		half_size;

	size = ft_array_size(&vis->lem.links);
	half_size = vis->roomsize / 2;
	while (size--)
	{
		if (ft_array_get(&vis->lem.links, size, (void **)&link) == 0)
		{
			start.x = (int)(link->left->x * vis->roomsize + half_size);
			start.y = (int)(link->left->y * vis->roomsize + half_size);
			end.x = (int)(link->right->x * vis->roomsize + half_size);
			end.y = (int)(link->right->y * vis->roomsize + half_size);
			SDL_SetRenderDrawColor(vis->ren, 0xFF, 0xFF, 0x00, 0x00);
			SDL_RenderDrawLine(vis->ren, start.x, start.y, end.x, end.y);
		}
	}
}

void	draw_rooms(t_vis *vis)
{
	size_t		size;
	t_roomdata	*room;
	SDL_Rect 	roomrect;

	size = ft_array_size(&vis->lem.rooms);
	while (size--)
	{
		if (ft_array_get(&vis->lem.rooms, size, (void **)&room) == 0)
		{
			roomrect.w = vis->roomsize * 0.95;
			roomrect.h = vis->roomsize * 0.95;
			roomrect.x = room->x * vis->roomsize + (vis->roomsize - roomrect.w) / 2;
			roomrect.y = room->y * vis->roomsize + (vis->roomsize - roomrect.h) / 2;;
			SDL_SetRenderDrawColor(vis->ren, 0xFF, 0x00, 0x00, 0x00);
			SDL_RenderDrawRect(vis->ren, &roomrect);
		}
	}
}

void	draw_ants(t_vis *vis)
{
	size_t		size;
	t_roomdata	*room;
	SDL_Rect 	srcrect;
	SDL_Rect 	roomrect;

	size = ft_array_size(&vis->lem.rooms);
	while (size--)
	{
		if (ft_array_get(&vis->lem.rooms, size, (void **)&room) == 0)
		{
			srcrect.x = 0 + (vis->tim_count % vis->antsimg.nframes) *
							(vis->antsimg.w / vis->antsimg.nframes);
			srcrect.y = 0;
			srcrect.w = (vis->antsimg.w / vis->antsimg.nframes);
			srcrect.h = vis->antsimg.h;
			roomrect.w = vis->roomsize * 0.95;
			roomrect.h = vis->roomsize * 0.95;
			roomrect.x = room->x * vis->roomsize + (vis->roomsize - roomrect.w) / 2;
			roomrect.y = room->y * vis->roomsize + (vis->roomsize - roomrect.h) / 2;;
			SDL_RenderCopyEx(vis->ren, vis->ants, &srcrect, &roomrect, 0, NULL , SDL_FLIP_NONE);
		}
	}
}

t_result	process_move(t_vis *vis, char *str)
{
	char		*s;
	int 		index;
	char		*end;
	t_roomdata	*rdata;

	while ((s = get_next_word(str, NULL)))
	{
		if (*s++ != 'L')
			return (ERR_NOT_MOVE);
		index = (int)ft_strtol(s, &end, 10);
		if (*end++ != '-')
			return (ERR_NOT_MOVE);
		if ((rdata = find_room_by_name(&vis->lem.rooms, end)) == NULL)
			return (ERR_NOT_MOVE);

	}
}

t_result	read_moves(t_vis *vis, int fd)
{
	int		res;
	char	*s;
	t_result	ret;

	while ((res = get_next_line(fd, &s)))
	{
		if (res < 0)
			return (ERR_GNL_ERROR);
		if ((ret = process_move(vis, s)) != RET_OK)
			return (ret);
		ft_strdel(&s);
	}
}

int		main(int ac, char *av[])
{
	t_vis			vis;
	int 			run;
	SDL_Event		e;
	SDL_Color		color;
	SDL_Point		text_point;
	int 			fd;
	t_result		res;

	ft_bzero(&vis, sizeof(vis));
	vis.window = NULL;
	vis.tim_count = 0;
	init_lem(&vis.lem);
	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
		fd = 0;
	res = read_file(&vis, fd);
	if (res == ERR_EMPTY_STR)
	{
		if (check_all(&vis.lem) == RET_OK)
		{
			vis.lemarr = ft_calloc(vis.lem.num_ants, sizeof(t_lemdata));


			read_moves(&vis, fd);
		}
	}
	recalc_room_size(&vis, 1000, 500);
	if (sdl_init(&vis) != 0)
		return (sdl_destroy(&vis));
	if (load_image(&vis) != 0)
		return (sdl_destroy(&vis));
	if (load_font(&vis) != 0)
		return (sdl_destroy(&vis));
	vis.timer = SDL_AddTimer(20, my_callbackfunc, &(vis.tim_count));
	run = 1;
	while (run) {
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				run = 0;
			if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					recalc_room_size(&vis, e.window.data1, e.window.data2);
			}
		}
		text_point.x = 10;
		text_point.y = 10;

		color.a = 255;
		color.r = 0;
		color.g = 0;
		color.b = 0;

		SDL_SetRenderDrawColor(vis.ren, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderClear(vis.ren);
		text_out(&vis, &text_point,"Привет муравьям!", color);

		SDL_SetRenderDrawColor(vis.ren, 0x00, 0x00, 0x00, 0x00);
		//SDL_RenderDrawRect(vis.ren, &roomrect);
		draw_links(&vis);
		draw_rooms(&vis);
		draw_ants(&vis);
		SDL_RenderPresent(vis.ren);
	}
	sdl_destroy(&vis);
	return (0);
}
