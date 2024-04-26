/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:17:32 by sshahary          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/22 09:17:21 by rpambhar         ###   ########.fr       */
=======
/*   Updated: 2024/04/25 12:09:58 by sshahary         ###   ########.fr       */
>>>>>>> fd187f723f43294ad024081255da789ba14a3e1c
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

int	remove_char(char *str, char c)
{
	int	new_index = 0;
	int	i = 0;

	while (str[i])
	{
		if (str[i] != c)
			str[new_index++] = str[i];
		i++;
	}
	str[new_index] = '\0'; // Null-terminate the string
	return (1);
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

int	ft_dstrlen(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
		i += 1;
	return (i);
}

char	*ft_strtok(char *str, char sep)
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
		if (i == 0 && *tok != sep)
		{
			i = 1;
			p = tok;
		}
		else if (i == 1 && *tok == sep)
		{
			*tok = '\0';
			tok += 1;
			break ;
		}
		tok++;
	}
	return (p);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
