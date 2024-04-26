/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:08:35 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/26 18:03:18 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstlast(t_lst *lst)
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
