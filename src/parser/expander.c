/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:19 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/21 14:04:13 by rpambhar         ###   ########.fr       */
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

int	check_and_expand(char **s, t_mini *mini)
{
	char	*expanded_str;
	int		i;
	char	*str;

	expanded_str = NULL;
	str = *s;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_quotes(str, &i, &expanded_str);
		if (str[i] == '\"')
			handle_dquotes(str, &i, &expanded_str, mini);
		if (str[i] == '$' && str[i + 1])
			handle_expansion(str, &i, &expanded_str, mini);
		else
		{
			expanded_str = ft_strnjoin(expanded_str, &str[i], 1);
			i++;
		}
	}
	free(str);
	*s = expanded_str;
	return (1);
}

int	handle_expansion(char *str, int *i, char **ex_str, t_mini *mini)
{
	int	sp;
	int	ep;
	char	*expansion;

	(*i)++;
	sp = (*i);
	if (str[*i] && str[*i] == '$')
	{
		(*i)++;
		expansion = ft_itoa((int)getpid());
		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
		free(expansion);
	}
	else if (str[*i] && str[*i] == '?')
	{
		(*i)++;
		expansion = ft_itoa(mini->exit_code);
		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
		free(expansion);
	}
	else
	{
		while (str[*i] && ft_isalnum(str[*i])) // also it can be _ . -
		{
			(*i)++;
			ep = *i;
		}
		char *temp = ft_substr(str, sp, ep - sp);
		expansion = get_env(temp, mini->env);
		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
		free(temp);
	}
	return (1);
}

int	handle_dquotes(char *str, int *i, char **ex_str, t_mini *mini)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
			handle_expansion(str, i, ex_str, mini);
		else
		{
			*ex_str = ft_strnjoin(*ex_str, &str[*i], 1);
			(*i)++;
		}
	}
	(*i)++;
	return (1);
}

int	handle_quotes(char *str, int *i, char **ex_str)
{
	int	sp;
	int	ep;

	(*i)++;
	sp = *i;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
		ep = *i;
	}
	(*i)++;
	*ex_str = ft_strnjoin(*ex_str, &str[sp], ep - sp);
	if (!(*ex_str))
		return (0);
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