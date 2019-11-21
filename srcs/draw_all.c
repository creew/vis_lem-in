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

void		draw_all(t_vis *vis)
{
	SDL_Color		color;
	SDL_Point		text_point;

	color.a = 255;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	text_point.x = 10;
	text_point.y = 10;

	SDL_SetRenderDrawColor(vis->ren, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderClear(vis->ren);
	text_out(vis, &text_point,"Привет муравьям!", color);

	SDL_SetRenderDrawColor(vis->ren, 0x00, 0x00, 0x00, 0x00);
	draw_links(vis);
	draw_rooms(vis);
	draw_ants(vis);
	draw_handles(vis);
	SDL_RenderPresent(vis->ren);
}
