/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:02:09 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/23 11:02:09 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static void	draw_quad(SDL_Renderer *ren, SDL_Point c, SDL_Point add, int q)
{
	if (q == 2)
		SDL_RenderDrawPoint(ren, c.x + add.x, c.y + add.y);
	else if (q == 1)
		SDL_RenderDrawPoint(ren, c.x + add.x, c.y - add.y);
	else if (q == 3)
		SDL_RenderDrawPoint(ren, c.x - add.x, c.y + add.y);
	else if (q == 4)
		SDL_RenderDrawPoint(ren, c.x - add.x, c.y - add.y);
}

void		draw_arc(SDL_Renderer *ren, SDL_Point c, int q, int r)
{
	SDL_Point	add;
	int			delta;
	int			error;

	add.x = 0;
	add.y = r;
	delta = 1 - 2 * r;
	while (add.y >= 0)
	{
		draw_quad(ren, c, add, q);
		error = 2 * (delta + add.y) - 1;
		if ((delta < 0) && (error <= 0))
			delta += (2 * ++add.x + 1);
		else if ((delta > 0) && (error > 0))
			delta -= (2 * --add.y + 1);
		else
			delta += 2 * (++add.x - add.y--);
	}
}

void		draw_round_rect(SDL_Renderer *ren, SDL_Rect *rect, int r)
{
	SDL_Point p;

	SDL_RenderDrawLine(ren, rect->x + r, rect->y,
		rect->x + rect->w - r, rect->y);
	SDL_RenderDrawLine(ren, rect->x + r, rect->y + rect->h,
		rect->x + rect->w - r, rect->y + rect->h);
	SDL_RenderDrawLine(ren, rect->x, rect->y + r, rect->x,
		rect->y + rect->h - r);
	SDL_RenderDrawLine(ren, rect->x + rect->w, rect->y + r,
		rect->x + rect->w, rect->y + rect->h - r);
	p.x = rect->x + rect->w - r - 1;
	p.y = rect->y + r;
	draw_arc(ren, p, 1, r);
	p.x = rect->x + rect->w - r - 1;
	p.y = rect->y + rect->h - r;
	draw_arc(ren, p, 2, r);
	p.x = rect->x + r + 1;
	p.y = rect->y + rect->h - r;
	draw_arc(ren, p, 3, r);
	p.x = rect->x + r + 1;
	p.y = rect->y + r;
	draw_arc(ren, p, 4, r);
}

void		draw_filled_round_rect(SDL_Renderer *ren, SDL_Rect *rect, int r)
{
	int		y0;
	int		x;
	int		x0;
	int		w;

	y0 = -1;
	while (++y0 < rect->h - 2 * r)
	{
		SDL_RenderDrawLine(ren, rect->x, rect->y + r + y0, rect->x + rect->w,
			rect->y + r + y0);
	}
	y0 = -1;
	while (++y0 < r)
	{
		x = (int)(sqrt(r * r - y0 * y0) + 0.5);
		w = rect->w - r * 2 + x * 2;
		x0 = (rect->w - w) / 2;
		SDL_RenderDrawLine(ren, rect->x + x0 + 1, rect->y + r - y0,
			rect->x + x0 + w, rect->y + r - y0);
		SDL_RenderDrawLine(ren, rect->x + x0 + 1, rect->y + rect->h - r + y0,
			rect->x + x0 + w, rect->y + rect->h - r + y0);
	}
}
