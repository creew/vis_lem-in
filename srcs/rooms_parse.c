/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:50:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 11:50:18 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

t_roomdata		*find_room_by_name(t_roomarr *rooms, const char *name)
{
	t_roomdata	*rdata;
	size_t		count;

	count = -1;
	while (ft_array_get(rooms, ++count, (void **)&rdata) == 0)
	{
		if (ft_strequ(name, rdata->name))
			return (rdata);
	}
	return (NULL);
}

static int		check_room_xy_exist(t_roomarr *rooms, int x, int y)
{
	t_roomdata	*rdata;
	size_t		count;

	count = -1;
	while (ft_array_get(rooms, ++count, (void **)&rdata) == 0)
	{
		if (rdata->x == x && rdata->y == y)
			return (1);
	}
	return (0);
}

static int		check_room_valid(const char *name)
{
	if (!name || !*name || *name == 'L' || *name == '#')
		return (0);
	return (1);
}

static t_result	add_roomdata(t_roomarr *arr, const char *name,
								const int *xy, int cmd)
{
	t_roomdata	*rdata;
	size_t		len;

	len = ft_strlen(name);
	rdata = ft_memalloc(sizeof(t_roomdata) + len * sizeof(char));
	if (rdata == NULL)
		return (ERR_ENOMEM);
	if (ft_array_add(arr, rdata) != 0)
	{
		ft_memdel((void **)&rdata);
		return (ERR_ENOMEM);
	}
	rdata->index = ft_array_size(arr) - 1;
	rdata->x = xy[0];
	rdata->y = xy[1];
	rdata->cmd = cmd;
	ft_strlcpy(rdata->name, name, len + 1);
	return (RET_OK);
}

t_result		add_lem_room(t_roomarr *rooms, char *str, int cmd)
{
	int		last;
	int		xy[2];
	char	*name;
	char	*s1;
	char	*s2;

	name = get_next_word(str, &last);
	if (!name || last)
		return (ERR_EMPTY_ROOM_NAME);
	if (!check_room_valid(ft_trim_spaces(name)))
		return (ERR_WRONG_ROOM_NAME);
	if (find_room_by_name(rooms, name))
		return (ERR_ROOM_NAME_DUPL);
	s1 = get_next_word(name + ft_strlen(name) + 1, &last);
	if (!s1 || last)
		return (ERR_WRONG_ROOM_ARG);
	s2 = get_next_word(s1 + ft_strlen(s1) + 1, &last);
	if (!s2)
		return (ERR_WRONG_ROOM_ARG);
	if (ft_safe_atoi(ft_trim_spaces(s1), &xy[0]) != FT_ATOI_OK ||
		ft_safe_atoi(ft_trim_spaces(s2), &xy[1]) != FT_ATOI_OK)
		return (ERR_WRONG_ROOM_ARG);
	if (check_room_xy_exist(rooms, xy[0], xy[1]))
		return (ERR_ROOM_XY_DUPL);
	return (add_roomdata(rooms, name, xy, cmd));
}
