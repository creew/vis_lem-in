/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_lemin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:33:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 10:33:52 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_LEMIN_H
# define VIS_LEMIN_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "libft.h"

typedef struct	s_antsimg {
	int		w;
	int 	h;
	int 	nframes;
}				t_antsimg;

typedef struct	s_vis {
	int				wwidth;
	int 			wheight;


	size_t			tim_count;
	t_antsimg		antsimg;
	SDL_Window		*window;
	SDL_Renderer	*ren;
	SDL_Texture		*ants;
	SDL_TimerID		timer;
}				t_vis;

void	print_sdl_error(const char *err);

int		sdl_init(t_vis *vis);
int 	load_image(t_vis *vis);
#endif
