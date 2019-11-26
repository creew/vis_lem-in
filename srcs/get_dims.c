/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dims.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 08:57:32 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/26 08:57:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

void	get_main_rect(SDL_Rect *rect, int ww, int wh)
{
	SDL_Rect	handles;
	SDL_Rect	info;

	get_info_rect(&info, ww, wh);
	get_handles_rect(&handles, ww, wh);
	rect->x = handles.w;
	rect->y = info.y + info.h;
	rect->w = ww - handles.w;
	rect->h = wh - rect->y;
}

void	get_handles_rect(SDL_Rect *rect, int ww, int wh)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = ww / 6;
	if (rect->w > 80)
		rect->w = 80;
	rect->h = wh;
}

void	get_handle_rect(SDL_Rect *rect, int index, int ww, int wh)
{
	SDL_Rect	handles;

	get_handles_rect(&handles, ww, wh);
	rect->x = 4;
	rect->y = 4 + (handles.w - 8) * index + 20 * index;
	rect->w = handles.w - 8;
	rect->h = handles.w - 8;
}

void	get_info_rect(SDL_Rect *rect, int ww, int wh)
{
	SDL_Rect	handles;

	get_handles_rect(&handles, ww, wh);
	rect->x = handles.x + handles.w;
	rect->y = 0;
	rect->w = ww - rect->x;
	rect->h = 25;
}
