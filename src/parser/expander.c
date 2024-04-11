/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:19 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/11 12:24:41 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expander(t_mini *mini)
{
	t_cmds	*temp;
	int		i;

	temp = mini->cmds;
	while (mini->cmds)
	{
		i = 0;
		check_and_expand(&mini->cmds->commad);
		while (mini->cmds->args && mini->cmds->args[i])
		{
			check_and_expand(&mini->cmds->args[i]);
			i++;
		}
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
	return (1);
}

int	check_and_expand(char **str)
{
	int	i;
	int	sp;
	char	*value;

	i = 0;
	sp = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '$' && ((*str)[i + 1] != '?' || (*str)[i + 1] != '$'))
		{
			sp = i + 1;
			break ;
		}
		i++;
	}
	value = getenv(&(*str)[sp]);
	if (value)
	{
		free(*str);
		(*str) = ft_strdup(value);
	}
	// if (value)
	// {
	// 	printf("Variable Value: %s\n", &str[sp]);
	// 	printf("Variable Value: %s\n", value);
	// }
	return (1);
}