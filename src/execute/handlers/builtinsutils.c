/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:17:32 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/09 22:24:34 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	remove_char(char *str, char c)
{
	int	new_index;
	int	i;

	new_index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			str[new_index++] = str[i];
		i++;
	}
	str[new_index] = '\0';
	return (1);
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
