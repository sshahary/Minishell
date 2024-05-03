/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:02:52 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/03 10:33:17 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_and_free_args(char ***args, int *n)
{
	int		i;
	char	*temp;
	char	**temp1;
	char	**temp2;

	i = 0;
	temp = (*args)[*n];
	temp1 = ft_split((*args)[*n], ' ');
	temp2 = *args;
	merge_arrays(args, temp1, n);
	free(temp);
	free(temp1);
	free(temp2);
}

int	expander(t_mini *mini)
{
	t_cmds	*temp;
	int		i;
	int		s_flag;

	s_flag = 0;
	temp = mini->cmds;
	while (mini->cmds)
	{
		i = 0;
		while (mini->cmds->args && mini->cmds->args[i])
		{
			if (!check_and_expand(&mini->cmds->args[i], mini, &s_flag))
				return (0);
			if (s_flag == 1)
			{
				s_flag = 0;
				replace_and_free_args(&mini->cmds->args, &i);
			}
			i++;
		}
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
	return (1);
}

int	check_and_expand(char **s, t_mini *mini, int *s_flag)
{
	char	*expanded_str;
	int		i;
	char	*str;
	(void) s_flag;

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
		{
			if (handle_expansion(str, &i, &expanded_str, mini))
				*s_flag = 1;
		}
		else
			expanded_str = ft_strnjoin(expanded_str, &str[i++], 1);
	}
	free(str);
	*s = expanded_str;
	return (1);
}

int	handle_expansion(char *str, int *i, char **ex_str, t_mini *mini)
{
	(*i)++;
	if (str[*i] && (str[*i] == '$' || str[*i] == '?'))
	{
		if (!handle_pid_exitcode_expansion(str, i, ex_str, mini))
			return (0);
	}
	else
	{
		if (!expand_and_join(str, i, ex_str, mini))
			return (0);
	}
	return (1);
}

int	handle_dquotes(char *str, int *i, char **ex_str, t_mini *mini)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$' && str[(*i) + 1] != '\"')
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
