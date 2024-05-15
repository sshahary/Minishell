/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:40:11 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/12 14:20:05 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_pid_exitcode_ex(char *str, int *i, char **ex_str, t_mini *m);
static int	expand_and_join(char *str, int *i, char **ex_str, t_mini *mini);

int	handle_expansion(char *str, int *i, char **ex_str, t_mini *mini)
{
	(*i)++;
	if (str[*i] && (str[*i] == '$' || str[*i] == '?'))
	{
		if (!handle_pid_exitcode_ex(str, i, ex_str, mini))
			return (0);
	}
	else
	{
		if (!expand_and_join(str, i, ex_str, mini))
			return (0);
	}
	return (1);
}

static int	expand_and_join(char *str, int *i, char **ex_str, t_mini *mini)
{
	int		ep;
	char	*expansion;
	char	*temp;
	int		sp;

	sp = (*i);
	while (str[*i] && ft_isalnum(str[*i]))
	{
		(*i)++;
		ep = *i;
	}
	temp = ft_substr(str, sp, ep - sp);
	expansion = get_env(temp, mini->env);
	if (!expansion || !expansion[0])
	{
		free(temp);
		return (0);
	}
	*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
	free(temp);
	return (1);
}

int	handle_dquotes(char *str, int *i, char **ex_str, t_mini *mini)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$' && str[(*i) + 1] != '\"' && str[(*i) + 1] != ' ')
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

static int	handle_pid_exitcode_ex(char *str, int *i, char **ex_str, t_mini *m)
{
	char	*expansion;

	if (str[*i] && str[*i] == '$')
	{
		(*i)++;
		expansion = ft_itoa((int)getpid());
		if (!expansion)
			return (0);
		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
		if (!(*ex_str))
			return (0);
		free(expansion);
	}
	else if (str[*i] && str[*i] == '?')
	{
		(*i)++;
		expansion = ft_itoa(m->exit_code);
		if (!expansion)
			return (0);
		*ex_str = ft_strnjoin(*ex_str, expansion, ft_strlen(expansion));
		if (!ex_str)
			return (0);
		free(expansion);
	}
	return (1);
}
