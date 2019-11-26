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
	size_t		index;
	t_linkdata	*link;
	SDL_Point	start;
	SDL_Point	end;
	t_rect		main;

	get_main_rect(&main, vis->wwidth, vis->wheight);
	index = -1;
	while (ft_array_get(&vis->lem.links, ++index, (void **)&link) == 0)
	{
		start.x = link->left->x * vis->roomsize + vis->roomsize / 2 + main.x;
		start.y = link->left->y * vis->roomsize + vis->roomsize / 2 + main.y;
		end.x = link->right->x * vis->roomsize + vis->roomsize / 2 + main.x;
		end.y = link->right->y * vis->roomsize + vis->roomsize / 2 + main.y;
		SDL_SetRenderDrawColor(vis->ren, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(vis->ren, start.x, start.y, end.x, end.y);
	}
}

static void		draw_handle(t_vis *vis, int src_index, int dst_index)
{
	SDL_Rect	srcrect;
	SDL_Rect	dstrect;

	srcrect.x = 0 + (src_index) * (vis->buttonsimg.w / vis->buttonsimg.nframes);
	srcrect.y = 0;
	srcrect.w = (vis->buttonsimg.w / vis->buttonsimg.nframes);
	srcrect.h = vis->buttonsimg.h;
	get_handle_rect(&dstrect, dst_index, vis->wwidth, vis->wheight);
	SDL_RenderCopy(vis->ren, vis->buttonsimg.texture, &srcrect, &dstrect);
}

void			draw_handles(t_vis *vis)
{
	SDL_Rect	handles;

	get_handles_rect(&handles, vis->wwidth, vis->wheight);
	SDL_SetRenderDrawColor(vis->ren, 0xFF, 0xFF, 0x00, 0xFF);
	draw_filled_round_rect(vis->ren, &handles, 10);
	draw_handle(vis, 0, 0);
	draw_handle(vis, vis->paused ? 1 : 3, 1);
	draw_handle(vis, 4, 2);
}
