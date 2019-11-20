/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_font.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:29:47 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 13:29:48 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

int		load_font(t_vis *vis)
{
	vis->font = TTF_OpenFont(NES_FONT, 12);
	if (vis->font == NULL)
	{
		print_sdl_error(TTF_GetError());
		return (1);
	}
	return (0);
}

void	text_out(t_vis *vis, SDL_Point *point, char *txt, SDL_Color color)
{
	SDL_Surface		*surface;
	SDL_Texture		*msg;
	SDL_Rect		rect;

	surface = TTF_RenderUTF8_Solid(vis->font, txt, color);
	msg = SDL_CreateTextureFromSurface(vis->ren, surface);
	rect.x = point->x;
	rect.y = point->y;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_RenderCopy(vis->ren, msg, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(msg);
}