/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_extra_pushswap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:42:05 by gphilipp          #+#    #+#             */
/*   Updated: 2021/12/24 14:49:18 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	list_already_ordered(int asc, t_list *plist, int *index)
{
	int			before;
	int			current;
	t_info		info;
	int			i;

	i = 0;
	info = list_int_info(plist);
	before = list_get_int(list_last(&plist));
	*index = 0;
	while (plist)
	{
		current = list_get_int(plist);
		if ((asc == 1 && current == info.min)
			|| (asc != 1 && current == info.max))
			*index = i;
		if (((asc == 1 && current < before) || (asc != 1 && current > before))
			&& !(current == info.min && before == info.max && asc == 1)
			&& !(current == info.max && before == info.min && asc != 1))
			return (0);
		plist = plist->next;
		before = current;
		i++;
	}
	return (1);
}

int	list_count_value_before(t_list *plist, t_list *current)
{
	int			value;
	int			i;

	i = 0;
	value = list_get_int(current);
	while (plist)
	{
		if (list_get_int(plist) < value)
			i++;
		plist = plist->next;
	}
	return (i);
}

int	list_get_int_index(t_list *plist, int value)
{
	int			i;

	i = -1;
	while (plist && ++i >= 0 && list_get_int(plist) != value)
		plist = plist->next;
	return (i);
}
