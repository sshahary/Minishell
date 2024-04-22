/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:17:32 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/22 09:17:21 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*strjoinslash(const char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = (char *)malloc(len_s1 + len_s2 + 2);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len_s1);
	if (len_s1 == 0 || s1[len_s1 - 1] != '/')
		result[len_s1++] = '/';
	ft_memcpy(result + len_s1, s2, len_s2 + 1);
	return (result);
}