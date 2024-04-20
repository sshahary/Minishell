/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:10:05 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/19 23:19:00 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
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
