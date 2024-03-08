/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:08:35 by rpambhar          #+#    #+#             */
/*   Updated: 2023/12/27 04:36:31 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_lst *lst)
{
	t_lst	*current;

	current = NULL;
	if (!lst)
		return (current);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}
