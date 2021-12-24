/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_extra_pushswap.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:29:14 by gphilipp          #+#    #+#             */
/*   Updated: 2021/12/24 14:55:52 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_EXTRA_PUSHSWAP_H
# define LIST_EXTRA_PUSHSWAP_H

int			list_already_ordered(int asc, t_list *plist, int *index);
int			list_count_value_before(t_list *plist, t_list *current);
int			list_get_int_index(t_list *plist, int value);
void		list_print_str(t_list *plist);
void		ft_putstr(char *s);

#endif
