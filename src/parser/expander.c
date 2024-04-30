/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:48:19 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/30 18:15:50 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_expansion(char *str, int *i, char **ex_str, t_mini *mini)
{
	int		sp;
	int		ep;
	char	*expansion;
	char	*temp;

	(*i)++;
	sp = (*i);
	if (str[*i] && (str[*i] == '$' || str[*i] == '?'))
	{
		if (!handle_pid_exitcode_expansion(str, i, ex_str, mini))
			return (0);
	}
	else
	{
		while (str[*i] && ft_isalnum(str[*i]))
		{
			(*i)++;
			ep = *i;
		}
		temp = ft_substr(str, sp, ep - sp);
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
