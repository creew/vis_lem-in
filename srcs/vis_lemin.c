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
#include "process_events.h"
#include <fcntl.h>

void		init_lem(t_lemin *lem)
{
	ft_bzero(lem, sizeof(*lem));
	ft_array_init(&lem->rooms, 128);
	ft_array_init(&lem->links, 128);
	ft_array_init(&lem->paths, 128);
}

t_result	process_move(t_vis *vis, char *str)
{
	char		*s;
	int 		index;
	char		*end;
	int			last;
	t_roomdata	*rdata;

	while ((s = get_next_word(str, &last)))
	{
		if (*s++ != 'L')
			return (ERR_NOT_MOVE);
		index = (int)ft_strtol(s, &end, 10);
		if (*end++ != '-')
			return (ERR_NOT_MOVE);
		if ((rdata = find_room_by_name(&vis->lem.rooms, end)) == NULL)
			return (ERR_NOT_MOVE);
		if (last)
			break;
		str = s + ft_strlen(s) + 1;
	}
}

t_result	read_moves(t_vis *vis, int fd)
{
	int			res;
	char		*s;
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

	SDL_Color		color;
	SDL_Point		text_point;
	t_result		res;

	ft_bzero(&vis, sizeof(vis));
	vis.window = NULL;
	vis.tim_count = 0;
	init_lem(&vis.lem);
	if (ac != 2 || (vis.lem.fd = open(av[1], O_RDONLY)) == -1)
		vis.lem.fd = 0;
	res = read_file(&vis, vis.lem.fd);
	if (res == ERR_EMPTY_STR)
	{
		if (check_all(&vis.lem) == RET_OK)
		{
			vis.lemarr = ft_calloc(vis.lem.num_ants, sizeof(t_lemdata));
			read_moves(&vis, vis.lem.fd);
		}
	}
	recalc_room_size(&vis, 1000, 500);
	if (sdl_init(&vis) != 0)
		return (vis_destroy(&vis));
	if (load_image_ants(&vis) != 0)
		return (vis_destroy(&vis));
	if (load_font(&vis) != 0)
		return (vis_destroy(&vis));
	vis.anim_tim = add_anim_timer(&vis.tim_count);
	vis.moves_tim = add_moves_timer(&vis);
	run = 1;
	while (run)
	{
		run = process_event(&vis);
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
	vis_destroy(&vis);
	return (0);
}
