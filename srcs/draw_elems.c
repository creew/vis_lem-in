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
	t_point		start;
	t_point		end;
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
			SDL_RenderDrawLine(vis->ren, start.x, start.y, end.x, end.y);
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
			SDL_RenderDrawRect(vis->ren, &roomrect);
			point.x = roomrect.x + 5;
			point.y = roomrect.y + 5;
			if (room->cmd == LEM_CMD_START || room->cmd == LEM_CMD_END)
			{
				color.a = 255;
				color.r = 0;
				color.g = 0;
				color.b = 0;
				text_out(vis, &point, room->cmd == LEM_CMD_START ?
					"start":"end", color);
			}
			else
			{
				color.a = 255;
				color.r = 0;
				color.g = 0;
				color.b = 0;
				text_out(vis, &point, room->name, color);
			}
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
	size_t		size;
	t_lemdata	*ldata;

	size = ft_array_size(&vis->curlems);
	while (size--)
	{
		if (ft_array_get(&vis->curlems, size, (void **)&ldata) == 0)
		{
			draw_ant(vis, ldata);
		}
	}
}

void 	draw_handles(t_vis *vis)
{
	SDL_Rect 	srcrect;
	SDL_Rect 	dstrect;
	t_rect		handles;
	int 		index;

	index = -1;
	get_handles_rect(&handles, vis->wwidth, vis->wheight);
	while (++index < vis->buttonsimg.nframes)
	{
		srcrect.x = 0 + (index) * (vis->buttonsimg.w / vis->buttonsimg.nframes);
		srcrect.y = 0;
		srcrect.w = (vis->buttonsimg.w / vis->buttonsimg.nframes);
		srcrect.h = vis->buttonsimg.h;


		dstrect.w = (int)(handles.w);
		dstrect.h = (int)(handles.w);
		dstrect.x = handles.x;
		dstrect.y = handles.y + index * handles.w + index * 20;
		SDL_RenderCopy(vis->ren, vis->buttonsimg.texture, &srcrect, &dstrect);
	}
}
