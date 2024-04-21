/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:46:18 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/21 13:52:41 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0' && j < n)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}
