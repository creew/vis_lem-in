/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:59:48 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 11:59:48 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

int		count_numbers(char *str)
{
	char	*s;
	int		count;

	count = 0;
	while ((s = ft_strchr(str, ' ')))
	{
		s++;
		if (s != (str + 1))
			count++;
		str = s;
	}
	if (*str != '\0')
		count++;
	return (count);
}

char	*get_next_word(char *str, int *last)
{
	char	*end;

	if (last)
		*last = 0;
	while ((end = ft_strchr(str, ' ')))
	{
		if (end != str)
			break ;
		str = end + 1;
	}
	if (*str != '\0')
	{
		if (end == NULL)
		{
			if (last)
				*last = 1;
		}
		else
			*end = '\0';
		return (str);
	}
	return (NULL);
}
