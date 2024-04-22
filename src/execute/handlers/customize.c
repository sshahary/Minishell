/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:17:32 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/22 04:35:14 by sshahary         ###   ########.fr       */
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

// static char	*strnew(size_t size)
// {
// 	char	*str;
// 	if (size == 0)
// 		return (NULL);

// 	str = (char *)ft_calloc(size + 1, sizeof(char));
// 	if (str == NULL)
// 		return (NULL);
// 	return (str);
// }

// void	strclr(char *str)
// {
// 	if (str != NULL)
// 	{
// 		while (*str != '\0')
// 		{
// 			*str = '\0';
// 			str++;
// 		}
// 	}
// }

// void	my_strcpy(char *dest, const char *src)
// {
// 	if (!(src) || !(*src))
// 		return ;
// 	while (*src != '\0')
// 	{
// 		*dest = *src;
// 		dest++;
// 		src++;
// 	}
// 	*dest = '\0';
// }

// int main() {
// 	char *source = 0;
// 	char destination[20];

// 	my_strcpy(destination, source);
// 	printf("Copied string: %s\n", destination);

// 	return 0;
// }

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

// size_t		ft_pstrlen(char **str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != NULL)
// 		i += 1;
// 	return (i);
// }

char	*ft_strtok(char *str, char sepa)
{
	static char	*tok = NULL;
	char		*p;
	int			i;

	i = 0;
	p = NULL;
	if (str != NULL)
		tok = ft_strdup(str);
	while (*tok != '\0')
	{
		if (i == 0 && *tok != sepa)
		{
			i = 1;
			p = tok;
		}
		else if (i == 1 && *tok == sepa)
		{
			*tok = '\0';
			tok += 1;
			break ;
		}
		tok++;
	}
	return (p);
}
