/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:43:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 11:43:32 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

int		load_image_ants(t_vis *vis)
{
	SDL_Surface		*temp_surf;

	temp_surf = IMG_Load(ANTS_IMG);
	if (temp_surf == NULL)
	{
		print_sdl_error(IMG_GetError());
		return (1);
	}
	vis->antsimg.texture = SDL_CreateTextureFromSurface(vis->ren, temp_surf);
	if (vis->antsimg.texture == NULL)
	{
		SDL_FreeSurface(temp_surf);
		print_sdl_error(SDL_GetError());
		return (1);
	}
	vis->antsimg.w = temp_surf->w;
	vis->antsimg.h = temp_surf->h;
	vis->antsimg.nframes = 8;
	SDL_FreeSurface(temp_surf);
	return (0);
}

int		load_image_buttons(t_vis *vis)
{
	SDL_Surface		*temp_surf;

	temp_surf = IMG_Load(PLAY_PAUSE_IMG);
	if (temp_surf == NULL)
	{
		print_sdl_error(IMG_GetError());
		return (1);
	}
	vis->buttonsimg.texture = SDL_CreateTextureFromSurface(vis->ren, temp_surf);
	if (vis->buttonsimg.texture == NULL)
	{
		print_sdl_error(SDL_GetError());
		SDL_FreeSurface(temp_surf);
		return (1);
	}
	vis->buttonsimg.w = temp_surf->w;
	vis->buttonsimg.h = temp_surf->h;
	vis->buttonsimg.nframes = 5;
	SDL_FreeSurface(temp_surf);
	return (0);
}
