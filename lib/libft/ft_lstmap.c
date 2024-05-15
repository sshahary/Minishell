/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:00:25 by rpambhar          #+#    #+#             */
/*   Updated: 2023/12/27 04:36:43 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst	*element;
	t_lst	*new;
	void	*temp;

	new = NULL;
	while (lst)
	{
		temp = (f)(lst->content);
		element = ft_lstnew(temp);
		if (!(element))
		{
			free(temp);
			ft_lstclear(&new, del);
			return (NULL);
		}
		if (new == NULL)
			new = element;
		else
			ft_lstadd_back(&new, element);
		lst = lst->next;
	}
	return (new);
}
