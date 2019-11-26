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

TTF_Font	*load_font(int pt_size)
{
	TTF_Font	*font;

	font = TTF_OpenFont(NES_FONT, pt_size);
	if (font == NULL)
		print_sdl_error(TTF_GetError());
	return (font);
}

void		text_out(t_vis *vis, SDL_Rect *to, char *txt, SDL_Color color)
{
	SDL_Surface		*surface;
	SDL_Texture		*msg;
	SDL_Rect		rect;
	float			scale;

	surface = TTF_RenderUTF8_Solid(vis->font, txt, color);
	msg = SDL_CreateTextureFromSurface(vis->ren, surface);
	scale = (float)surface->h / (float)(to->h - 4);
	rect.w = (int)((float)surface->w / scale);
	rect.h = to->h - 4;
	rect.x = to->x + (vis->roomsize - rect.w) / 2;
	rect.y = to->y + 2;
	SDL_RenderCopy(vis->ren, msg, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(msg);
}

void		info_text_out(t_vis *vis, SDL_Point *point, char *txt,
	SDL_Color color)
{
	SDL_Surface		*surface;
	SDL_Texture		*msg;
	SDL_Rect		rect;

	surface = TTF_RenderUTF8_Solid(vis->info_font, txt, color);
	msg = SDL_CreateTextureFromSurface(vis->ren, surface);
	rect.x = point->x;
	rect.y = point->y;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_RenderCopy(vis->ren, msg, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(msg);
}
