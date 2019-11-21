#include "vis_lemin.h"

void	get_main_rect(t_rect *rect, int ww, int wh)
{
	t_rect	handles;

	get_handles_rect(&handles, ww, wh);
	rect->x = handles.w;
	rect->y = 0;
	rect->w = wh - handles.w;
	rect->h = wh;
}

void	get_handles_rect(t_rect *rect, int ww, int wh)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = ww / 6;
	if (rect->w > 80)
		rect->w = 80;
	rect->h = wh;
}