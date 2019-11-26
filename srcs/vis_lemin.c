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

int			init_all(t_vis *vis)
{
	if (sdl_init(vis) != 0)
		return (1);
	if (load_image_ants(vis) != 0)
		return (1);
	if (load_image_buttons(vis) != 0)
		return (1);
	if ((vis->font = load_font(12)) == NULL)
		return (1);
	if ((vis->info_font = load_font(20)) == NULL)
		return (1);
	vis->speed = 5;
	vis->anim_tim = add_anim_timer(vis);
	vis->moves_tim = add_moves_timer(vis);
	vis->at_start = vis->lem.num_ants;
	return (0);
}

int			main(int ac, char *av[])
{
	t_vis			vis;
	t_result		res;

	ft_bzero(&vis, sizeof(vis));
	init_lem(&vis.lem);
	if (ac != 2 || (vis.lem.fd = open(av[1], O_RDONLY)) == -1)
		vis.lem.fd = 0;
	res = read_file(&vis);
	if (res == ERR_EMPTY_STR)
	{
		if (check_all(&vis.lem) == RET_OK)
			vis.lemarr = ft_calloc(vis.lem.num_ants, sizeof(t_lemdata));
		else
			return (vis_destroy(&vis, 1));
	}
	else
		return (vis_destroy(&vis, 1));
	ft_array_init(&vis.curlems, 64);
	recalc_room_size(&vis, 1000, 500);
	if (init_all(&vis))
		return (vis_destroy(&vis, 1));
	while (process_event(&vis))
		draw_all(&vis);
	vis_destroy(&vis, 0);
	return (0);
}
