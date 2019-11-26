/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fat_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:20:09 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/26 17:20:09 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static void	fill_rect_texture(SDL_Texture *text, int width, int height)
{
	Uint32			*pixels;
	int				pitch;
	int				tw;
	Uint32			color;
	SDL_PixelFormat	*pixel_format;

	if (SDL_LockTexture(text, NULL, (void**)&pixels, &pitch))
		print_sdl_error(SDL_GetError());
	pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	color = SDL_MapRGB(pixel_format, 255, 0, 0);
	while (height--)
	{
		tw = width;
		while (tw--)
			pixels[height * (pitch / sizeof(unsigned int)) + tw] = color;
	}
	SDL_FreeFormat(pixel_format);
	SDL_UnlockTexture(text);
}

static void	fill_rects(t_fatline *fl, SDL_Point *start, int width, int heigth)
{
	fl->src.x = 0;
	fl->src.y = 0;
	fl->src.w = width;
	fl->src.h = heigth;
	fl->dst.x = start->x;
	fl->dst.y = start->y;
	fl->dst.w = width;
	fl->dst.h = heigth;
}

void		draw_line(SDL_Renderer *ren, SDL_Point *start,
	SDL_Point *end, int heigth)
{
	SDL_Texture	*text;
	int			width;
	Uint32		format;
	t_fatline	fl;

	width = (int)sqrtf((end->x - start->x) * (end->x - start->x) +
		(end->y - start->y) * (end->y - start->y));
	text = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, width, heigth);
	SDL_QueryTexture(text, &format, NULL, NULL, NULL);
	fill_rect_texture(text, width, heigth);
	fl.angle = atan2f(end->y - start->y, end->x - start->x) * 180 / M_PI;
	fill_rects(&fl, start, width, heigth);
	fl.center.x = fl.src.x;
	fl.center.y = fl.src.h / 2;
	SDL_RenderCopyEx(ren, text, &fl.src, &fl.dst, fl.angle, &fl.center,
		SDL_FLIP_NONE);
	SDL_DestroyTexture(text);
}
