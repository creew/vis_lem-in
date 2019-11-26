/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:49:38 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 15:49:38 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

t_result	is_start_end_exists(t_roomarr *arr, t_borders *se)
{
	int			start_count;
	int			end_count;
	t_roomdata	*rdata;
	size_t		index;

	index = -1;
	start_count = 0;
	end_count = 0;
	while (ft_array_get(arr, ++index, (void **)&rdata) == 0)
	{
		if (rdata->cmd == LEM_CMD_START)
		{
			se->start = rdata;
			start_count++;
		}
		if (rdata->cmd == LEM_CMD_END)
		{
			se->end = rdata;
			end_count++;
		}
	}
	return (start_count == 1 && end_count == 1 ? RET_OK : ERR_NO_START_OR_END);
}

t_result	check_all(t_lemin *lem)
{
	t_result	res;

	if (lem->links.num_elems == 0)
		return (ERR_NO_LINKS);
	if ((res = is_start_end_exists(&lem->rooms, &lem->se)) != RET_OK)
		return (res);
	return (RET_OK);
}
