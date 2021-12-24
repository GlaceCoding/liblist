/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_shift.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:18:44 by gphilipp          #+#    #+#             */
/*   Updated: 2021/12/24 15:05:57 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

void	*list_shift(t_list **plist)
{
	t_list		*del;
	void		*data;

	del = (*plist);
	data = del->data;
	if ((*plist)->next)
		*plist = (*plist)->next;
	else
		*plist = NULL;
	free(del);
	return (data);
}

void	*list_pop(t_list **plist)
{
	int			i;

	i = 0;
	while (*plist && (*plist)->next)
		plist = &((*plist)->next);
	if (*plist)
		return (list_shift(plist));
	return (NULL);
}

t_list	*list_slice(t_list **plist, int start, int deleteCount)
{
	t_list		*newlist;

	newlist = NULL;
	while (*plist && deleteCount)
	{
		if (start <= 0 && deleteCount--)
			list_push(&newlist, list_shift(plist));
		else
			plist = &((*plist)->next);
		start--;
	}
	return (newlist);
}

t_list	*list_map(t_list **plist, int (*map)(t_list **item, int index,
											t_list **plist))
{
	t_list		*newlist;
	t_list		**item;
	int			i;

	i = 0;
	item = plist;
	newlist = NULL;
	while (*item)
	{
		if (!(*map)(item, i, plist))
			list_push(&newlist, list_shift(item));
		else
			item = &((*item)->next);
		i++;
	}
	return (newlist);
}

int	list_clear(t_list **plist)
{
	int			i;

	i = 0;
	while (*plist && ++i)
		list_free_data(list_shift(plist));
	return (i);
}
