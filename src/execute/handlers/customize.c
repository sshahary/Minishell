/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:17:32 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/21 13:23:26 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*strnew(size_t size)
{
	char	*str;
	if (size == 0)
		return (NULL);

	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

void	strclr(char *str)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			*str = '\0';
			str++;
		}
	}
}

void	ft_pfree(void **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}