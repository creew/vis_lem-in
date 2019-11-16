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

int 	load_image(t_vis *vis)
{
	SDL_Surface		*temp_surf;

	temp_surf = IMG_Load("all_ants.png");
	if (temp_surf == NULL) {
		print_sdl_error("Can't load image");
		print_sdl_error(IMG_GetError());
		return (1);
	}
	vis->ants = SDL_CreateTextureFromSurface(vis->ren, temp_surf);
	if (vis->ants == NULL) {
		print_sdl_error("Can't create texture from surface: ");
		print_sdl_error(SDL_GetError());
		SDL_FreeSurface(temp_surf);
		return (1);
	}
	vis->antsimg.w = temp_surf->w;
	vis->antsimg.h = temp_surf->h;
	vis->antsimg.nframes = 8;
	SDL_FreeSurface(temp_surf);
	return (0);
}
