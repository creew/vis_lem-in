/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:54:44 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/18 08:54:45 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static void		get_lem_cmd(char *str, int *cmd)
{
	if (*str == '#' && *(str + 1) == '#')
	{
		ft_trim_spaces(str + 2);
		if (ft_strequ(str + 2, "start"))
			*cmd = LEM_CMD_START;
		else if (ft_strequ(str + 2, "end"))
			*cmd = LEM_CMD_END;
		else
			*cmd = LEM_CMD_UNKNOWN;
	}
}

static t_result	parse_not_comment_str(t_lemin *lem, char *s,
	int *is_rooms, int cmd)
{
	if (*is_rooms && count_numbers(s) == 3)
		return (add_lem_room(&lem->rooms, s, cmd));
	*is_rooms = 0;
	return (add_lem_link(&lem->rooms, &lem->links, s));
}

static t_result	read_rooms_and_links(int fd, t_lemin *lem)
{
	int			is_rooms;
	char		*s;
	t_result	res;
	int			cmd;

	cmd = LEM_CMD_NONE;
	is_rooms = 1;
	while ((res = get_next_line(fd, &s)))
	{
		if (res < 0)
			return (ERR_GNL_ERROR);
		if (*s != '#')
		{
			if ((res = parse_not_comment_str(lem, s, &is_rooms, cmd)) != RET_OK)
			{
				ft_strdel(&s);
				return (res);
			}
			cmd = LEM_CMD_NONE;
		}
		else
			get_lem_cmd(s, &cmd);
		ft_strdel(&s);
	}
	return (RET_OK);
}

int				read_file(t_vis *vis)
{
	char	*s;
	int		res;
	t_lemin	*lem;

	lem = &vis->lem;
	while ((res = get_next_line(vis->lem.fd, &s)))
	{
		if (res < 0)
			return (ERR_READ_ANTS_NUMBER);
		if (*s != '#')
			break ;
		ft_strdel(&s);
	}
	if (res == 0)
		return (ERR_READ_ANTS_NUMBER);
	res = ft_safe_atoi(s, &lem->num_ants);
	ft_strdel(&s);
	if (res != FT_ATOI_OK || lem->num_ants < 1)
		return (ERR_WRONG_ANTS_NUMBER);
	return (read_rooms_and_links(vis->lem.fd, lem));
}
