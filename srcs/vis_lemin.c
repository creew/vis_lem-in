/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_lemin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:33:38 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 10:33:39 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"
#include <fcntl.h>

void		init_lem(t_lemin *lem)
{
	ft_bzero(lem, sizeof(*lem));
	ft_array_init(&lem->rooms, 128);
	ft_array_init(&lem->links, 128);
	ft_array_init(&lem->paths, 128);
}

int		main(int ac, char *av[])
{
	t_vis			vis;
	t_result		res;

	ft_bzero(&vis, sizeof(vis));
	vis.window = NULL;
	vis.tim_count = 0;
	init_lem(&vis.lem);
	if (ac != 2 || (vis.lem.fd = open(av[1], O_RDONLY)) == -1)
		vis.lem.fd = 0;
	res = read_file(&vis);
	if (res == ERR_EMPTY_STR)
	{
		if (check_all(&vis.lem) == RET_OK)
			vis.lemarr = ft_calloc(vis.lem.num_ants, sizeof(t_lemdata));
		else
			return (vis_destroy(&vis));
	}
	else
		return (vis_destroy(&vis));
	ft_array_init(&vis.curlems, 64);
	recalc_room_size(&vis, 1000, 500);
	if (sdl_init(&vis) != 0)
		return (vis_destroy(&vis));
	if (load_image_ants(&vis) != 0)
		return (vis_destroy(&vis));
	if (load_image_buttons(&vis) != 0)
		return (vis_destroy(&vis));
	if (load_font(&vis) != 0)
		return (vis_destroy(&vis));
	vis.anim_tim = add_anim_timer(&vis.tim_count);
	vis.moves_tim = add_moves_timer(&vis);
	while (process_event(&vis))
		draw_all(&vis);
	vis_destroy(&vis);
	return (0);
}
