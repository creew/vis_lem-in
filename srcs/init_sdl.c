/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:35:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 11:35:11 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static int	create_renderer(t_vis *vis)
{
	vis->ren = SDL_CreateRenderer(vis->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (vis->ren == NULL)
	{
		print_sdl_error("SDL_CreateRenderer");
		return (1);
	}
	SDL_SetRenderDrawColor(vis->ren, 0x00, 0xFF, 0x00, 0xFF);
	return (0);
}

static int	create_window(t_vis *vis)
{
	vis->window = SDL_CreateWindow("Hello, SDL 2!", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, vis->wwidth,
		vis->wheight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (vis->window == NULL)
	{
		print_sdl_error("SDL_CreateWindow");
		return (1);
	}
	SDL_SetWindowMinimumSize(vis->window, 1000, 300);
	return (0);
}

int			sdl_init(t_vis *vis)
{
	int		flags;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
	{
		print_sdl_error("Init");
		return (1);
	}
	if (create_window(vis) != 0)
		return (1);
	if (create_renderer(vis) != 0)
		return (1);
	flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		print_sdl_error(IMG_GetError());
		return (1);
	}
	if (TTF_Init() != 0)
	{
		print_sdl_error(TTF_GetError());
		return (1);
	}
	return (0);
}
