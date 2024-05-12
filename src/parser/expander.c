/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:02:52 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/12 14:44:26 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	replace_and_free_args(char ***args, int *n, int *s_flag);
static int	handle_quotes(char *str, int *i, char **ex_str);
static void	check_and_ex_helper(char *str, char **es, t_mini *mini, int *sf);

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
			{
				remove_element(&mini->cmds->args, i);
				i--;
			}
			if (s_flag == 1)
				replace_and_free_args(&mini->cmds->args, &i, &s_flag);
			i++;
		}
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
	clean_cmds(mini);
	return (1);
}

int	check_and_expand(char **s, t_mini *mini, int *s_flag)
{
	char	*expanded_str;
	char	*str;

	expanded_str = NULL;
	str = *s;
	check_and_ex_helper(str, &expanded_str, mini, s_flag);
	if (!expanded_str)
		return (0);
	else
	{
		free(str);
		*s = expanded_str;
	}
	return (1);
}

static void	check_and_ex_helper(char *str, char **es, t_mini *mini, int *sf)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_quotes(str, &i, es);
		else if (str[i] == '\"')
			handle_dquotes(str, &i, es, mini);
		else if (str[i] == '$' && str[i + 1])
		{
			if (handle_expansion(str, &i, es, mini))
				*sf = 1;
		}
		else
			*es = ft_strnjoin(*es, &str[i++], 1);
	}
}

static void	replace_and_free_args(char ***args, int *n, int *s_flag)
{
	char	*temp;
	char	**temp1;
	char	**temp2;

	*s_flag = 0;
	temp = (*args)[*n];
	temp1 = ft_split((*args)[*n], ' ');
	temp2 = *args;
	merge_arrays(args, temp1, n);
	free(temp);
	free(temp1);
	free(temp2);
}

static int	handle_quotes(char *str, int *i, char **ex_str)
{
	int	sp;
	int	ep;

	(*i)++;
	sp = *i;
	if (str[*i] == '\'')
	{
		(*i)++;
		return (1);
	}
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
