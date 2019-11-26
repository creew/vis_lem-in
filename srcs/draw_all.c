/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:58:24 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/20 11:58:24 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"
#include "ft_printf.h"

SDL_Color	get_color(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void		draw_info(t_vis *vis)
{
	char		str[128];
	SDL_Rect	info;
	SDL_Point	point;
	SDL_Color	color;

	get_info_rect(&info, vis->wwidth, vis->wheight);
	point.x = info.x + 5;
	point.y = info.y + 2;
	ft_sprintf(str, "at start: %-3d, at finish: %-3d, speed: %-3d",
		vis->at_start, vis->finished, vis->speed);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	info_text_out(vis, &point, str, color);
}

void		draw_all(t_vis *vis)
{
	SDL_SetRenderDrawColor(vis->ren, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderClear(vis->ren);
	SDL_SetRenderDrawColor(vis->ren, 0x00, 0x00, 0x00, 0x00);
	draw_links(vis);
	draw_rooms(vis);
	draw_ants(vis);
	draw_handles(vis);
	draw_info(vis);
	SDL_RenderPresent(vis->ren);
}
