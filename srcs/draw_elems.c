/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:10:52 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/20 11:10:52 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

void			draw_links(t_vis *vis)
{
	size_t		size;
	t_linkdata	*link;
	SDL_Point	start;
	SDL_Point	end;
	float 		half_size;
	t_rect		main;

	get_main_rect(&main, vis->wwidth, vis->wheight);
	size = ft_array_size(&vis->lem.links);
	half_size = vis->roomsize / 2;
	while (size--)
	{
		if (ft_array_get(&vis->lem.links, size, (void **)&link) == 0)
		{
			start.x = (int)((float)link->left->x * vis->roomsize + half_size) + main.x;
			start.y = (int)((float)link->left->y * vis->roomsize + half_size) + main.y;
			end.x = (int)((float)link->right->x * vis->roomsize + half_size) + main.x;
			end.y = (int)((float)link->right->y * vis->roomsize + half_size) + main.y;
			SDL_SetRenderDrawColor(vis->ren, 0xFF, 0xFF, 0x00, 0x00);
			//SDL_RenderDrawLine(vis->ren, start.x, start.y, end.x, end.y);
			draw_line(vis->ren, &start, &end, 2);
		}
	}
}

void			draw_rooms(t_vis *vis)
{
	size_t		size;
	t_roomdata	*room;
	SDL_Rect 	roomrect;
	SDL_Point	point;
	SDL_Color	color;
	t_rect		main;

	get_main_rect(&main, vis->wwidth, vis->wheight);
	size = ft_array_size(&vis->lem.rooms);
	while (size--)
	{
		if (ft_array_get(&vis->lem.rooms, size, (void **)&room) == 0)
		{
			roomrect.w = vis->roomsize * 0.95f;
			roomrect.h = vis->roomsize * 0.95f;
			roomrect.x = main.x + room->x * vis->roomsize + (vis->roomsize - roomrect.w) / 2;
			roomrect.y = main.y + room->y * vis->roomsize + (vis->roomsize - roomrect.h) / 2;
			SDL_SetRenderDrawColor(vis->ren, 0xFF, 0x00, 0x00, 0x00);
			draw_filled_round_rect(vis->ren, &roomrect, ft_min(roomrect.w, roomrect.h) / 5);
			point.x = roomrect.x + 5;
			point.y = roomrect.y + 5;
			color.a = 255;
			color.r = 0;
			color.g = 0;
			color.b = 0;
			if (room->cmd == LEM_CMD_START || room->cmd == LEM_CMD_END)
				text_out(vis, &point, room->cmd == LEM_CMD_START ?
					"start":"end", color);
			else
				text_out(vis, &point, room->name, color);
		}
	}
}

static void		draw_ant(t_vis *vis, t_lemdata *ldata)
{
	SDL_Rect 	srcrect;
	SDL_Rect 	roomrect;
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
		ldata->angle, NULL , SDL_FLIP_NONE);
}

void	draw_ants(t_vis *vis)
{
	size_t		index;
	t_lemdata	*ldata;

	index = -1;
	while (ft_array_get(&vis->curlems, ++index, (void **)&ldata) == 0)
		draw_ant(vis, ldata);
}

static void	draw_handle(t_vis *vis, int src_index, int dst_index)
{
	SDL_Rect 	srcrect;
	SDL_Rect 	dstrect;

	srcrect.x = 0 + (src_index) * (vis->buttonsimg.w / vis->buttonsimg.nframes);
	srcrect.y = 0;
	srcrect.w = (vis->buttonsimg.w / vis->buttonsimg.nframes);
	srcrect.h = vis->buttonsimg.h;
	get_handle_rect(&dstrect, dst_index, vis->wwidth, vis->wheight);
	SDL_RenderCopy(vis->ren, vis->buttonsimg.texture, &srcrect, &dstrect);
}
void 		draw_handles(t_vis *vis)
{

	SDL_Rect	handles;

	get_handles_rect(&handles, vis->wwidth, vis->wheight);
	SDL_SetRenderDrawColor(vis->ren, 0xFF, 0xFF, 0x00, 0xFF);
	draw_filled_round_rect(vis->ren, &handles, 10);
	draw_handle(vis, 0, 0);
	draw_handle(vis, vis->paused ? 1 : 3, 1);
	draw_handle(vis, 4, 2);
}
