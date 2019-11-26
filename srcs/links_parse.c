/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:59:43 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 14:59:43 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

t_result		get_opposite_roomlink(
	t_linkarr *larr, size_t room_index, int n, size_t *index)
{
	t_linkdata	*ldata;
	size_t		size;

	size = ft_array_size(larr);
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if (room_index == ldata->left->index ||
				room_index == ldata->right->index)
			{
				if (!n--)
				{
					*index = room_index == ldata->left->index ?
						ldata->right->index : ldata->left->index;
					return (RET_OK);
				}
			}
		}
	}
	return (ERR_WRONG_LINK);
}

static int		is_link_exist(t_linkarr *larr, t_roomdata *l1, t_roomdata *l2)
{
	t_linkdata	*ldata;
	size_t		size;

	size = ft_array_size(larr);
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if ((l1 == ldata->left && l2 == ldata->right) ||
				(l1 == ldata->right && l2 == ldata->left))
				return (1);
		}
	}
	return (0);
}

static t_result	add_lemlink_list(t_linkarr *larr,
					t_roomdata *l1, t_roomdata *l2)
{
	t_linkdata	*ldata;

	if (!is_link_exist(larr, l1, l2))
	{
		ldata = ft_memalloc(sizeof(*ldata));
		if (!ldata)
			return (ERR_ENOMEM);
		if (ft_array_add(larr, ldata) != 0)
		{
			ft_memdel((void **)&ldata);
			return (ERR_ENOMEM);
		}
		ldata->left = l1;
		ldata->right = l2;
	}
	return (RET_OK);
}

/*
** FIXME: Wrong parsing links like "abc - def" and "a-b-c-def"
** -----
*/

t_result		add_lem_link(t_roomarr *rooms, t_linkarr *links, char *str)
{
	char		*r1;
	char		*r2;
	t_roomdata	*room1;
	t_roomdata	*room2;

	r1 = str;
	r2 = ft_strchr(str, '-');
	if (!r2)
	{
		if (!*ft_trim_spaces(str))
			return (ERR_EMPTY_STR);
		else
			return (ERR_WRONG_LINK);
	}
	*r2++ = '\0';
	if (!(room1 = find_room_by_name(rooms, ft_trim_spaces(r1))) ||
		!(room2 = find_room_by_name(rooms, ft_trim_spaces(r2))))
		return (ERR_WRONG_LINK_ROOM);
	if (ft_strequ(r1, r2))
		return (ERR_WRONG_LINK_TO_LINK);
	return (add_lemlink_list(links, room1, room2));
}
