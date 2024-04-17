/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:19 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/13 11:13:52 by rpambhar         ###   ########.fr       */
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
		if (!check_and_expand(&mini->cmds->commad, mini))
			return (0);
		while (mini->cmds->args && mini->cmds->args[i])
		{
			if (!check_and_expand(&mini->cmds->args[i], mini))
				return (0);
			i++;
		}
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
	return (1);
}

int	check_and_expand(char **str, t_mini *mini)
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
	value = get_env(&(*str)[sp], mini->env);
	if (value)
	{
		free(*str);
		(*str) = ft_strdup(value);
		if (!(*str))
			return (0);
	}
	return (1);
}

void	print_cmds(t_mini *mini)
{
	int		i;
	t_cmds	*temp;

	temp = mini->cmds;
	while (temp)
	{
		i = 0;
		printf("Command: %s\n", temp->commad);
		while (temp->args && temp->args[i])
		{
			printf("\tArg%d: <%s>\n", i, temp->args[i]);
			i++;
		}
		temp = temp->next;
	}
}

char	*get_env(const char *name, char **env)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			return &(env[i][name_len + 1]);
		}
		i++;
	}
	return (NULL);
}