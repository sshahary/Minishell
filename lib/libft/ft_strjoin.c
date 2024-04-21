/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:10:05 by rpambhar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/21 12:20:43 by sshahary         ###   ########.fr       */
=======
/*   Updated: 2024/04/20 16:36:16 by rpambhar         ###   ########.fr       */
>>>>>>> 9a5dc53570ffc118e8461fee94000a49a0ef1370
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	str = (char *) malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		if (i < ft_strlen(s1))
			*(str + i) = *(s1 + i);
		else
			*(str + i) = *(s2 + (i - ft_strlen(s1)));
		i++;
	}
	*(str + i) = '\0';
=======
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	while (s1 && s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != 0)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (s1)
		free(s1);
>>>>>>> 9a5dc53570ffc118e8461fee94000a49a0ef1370
	return (str);
}
