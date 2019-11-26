/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_roomants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:09:46 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/26 17:09:47 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static void		draw_room_name(t_vis *vis, SDL_Rect *roomrect, t_roomdata *room)
{
	SDL_Rect	rect;

	rect.x = roomrect->x;
	rect.y = roomrect->y;
	rect.w = vis->roomsize;
	rect.h = vis->roomsize / 3;
	if (room->cmd == LEM_CMD_START || room->cmd == LEM_CMD_END)
		text_out(vis, &rect, room->cmd == LEM_CMD_START ?
			"start" : "end", get_color(0, 0, 255, 255));
	else
		text_out(vis, &rect, room->name, get_color(0, 0, 255, 255));
}

void			draw_rooms(t_vis *vis)
{
	size_t		index;
	t_roomdata	*room;
	SDL_Rect	roomrect;
	SDL_Rect	main;

	get_main_rect(&main, vis->wwidth, vis->wheight);
	index = -1;
	while (ft_array_get(&vis->lem.rooms, ++index, (void **)&room) == 0)
	{
		roomrect.w = vis->roomsize * 0.95f;
		roomrect.h = vis->roomsize * 0.95f;
		roomrect.x = main.x + room->x * vis->roomsize +
			(vis->roomsize - roomrect.w) / 2;
		roomrect.y = main.y + room->y * vis->roomsize +
			(vis->roomsize - roomrect.h) / 2;
		SDL_SetRenderDrawColor(vis->ren, 0xFF, 0x00, 0x00, 0x00);
		draw_filled_round_rect(vis->ren, &roomrect, roomrect.w / 5);
		draw_room_name(vis, &roomrect, room);
	}
}

static void		draw_ant(t_vis *vis, t_lemdata *ldata)
{
	SDL_Rect	srcrect;
	SDL_Rect	roomrect;
	float		dim;
	t_rect		main;

	get_main_rect(&main, vis->wwidth, vis->wheight);
	srcrect.x = 0 + ((vis->tim_count + ldata->shift) % vis->antsimg.nframes) *
		(vis->antsimg.w / vis->antsimg.nframes);
	srcrect.y = 0;
	srcrect.w = (vis->antsimg.w / vis->antsimg.nframes);
	srcrect.h = vis->antsimg.h;
	dim = vis->roomsize * 0.95f;
	roomrect.w = (int)(dim);
	roomrect.h = (int)(dim);
	roomrect.x = main.x + (int)(ldata->x + (vis->roomsize - dim) / 2);
	roomrect.y = main.y + (int)(ldata->y + (vis->roomsize - dim) / 2);
	SDL_RenderCopyEx(vis->ren, vis->antsimg.texture, &srcrect, &roomrect,
		ldata->angle, NULL, SDL_FLIP_NONE);
}

void			draw_ants(t_vis *vis)
{
	size_t		index;
	t_lemdata	*ldata;
	t_lemdata	tmp;

	index = -1;
	while (ft_array_get(&vis->curlems, ++index, (void **)&ldata) == 0)
		draw_ant(vis, ldata);
	tmp.shift = 0;
	if (vis->at_start)
	{
		tmp.angle = 90;
		tmp.x = vis->lem.se.start->x * vis->roomsize;
		tmp.y = vis->lem.se.start->y * vis->roomsize;
		draw_ant(vis, &tmp);
	}
	if (vis->finished)
	{
		tmp.angle = 90;
		tmp.x = vis->lem.se.end->x * vis->roomsize;
		tmp.y = vis->lem.se.end->y * vis->roomsize;
		draw_ant(vis, &tmp);
	}
}
