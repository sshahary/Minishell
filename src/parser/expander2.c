/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:38:42 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/30 19:56:35 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expander(t_mini *mini)
{
	t_cmds	*temp;

	temp = mini->cmds;
	while (mini->cmds)
	{
		loop_args(mini, mini->cmds);
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
	return (1);
}

int	loop_args(t_mini *mini, t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (!check_and_expand(mini, cmd, &cmd->args[i], &i))
			return (0);
		i++;
	}
	return (0);
}

int	check_and_expand(t_mini *m, t_cmds *cmd, char **s, int *i)
{
	int		n;
	char	*expanded_str;
	char	*str;

	n = 0;
	expanded_str = NULL;
	str = *s;
	while (str[n])
	{
		if (str[n] == '\'')
			handle_quotes(str, &n, &expanded_str);
		if (str[n] == '\"')
			handle_dquotes(str, &n, &expanded_str, m);
		if (str[n] == '$' && str[n + 1])
			handle_dollar(m, cmd, &n, i);
		else
		{
			expanded_str = ft_strnjoin(expanded_str, &str[n], 1);
			n++;
		}
	}
	free(str);
	*s  = expanded_str;
	return (1);
}

int	handle_dollar(t_mini *m, t_cmds *cmd, int *n, int *i)
{
	char	*str;
	int		sp;
	int		ep;
	char	*temp;
	char	**array;
	char	*expansion;
	(void) m;

	str = cmd->args[*i];
	(*n)++;
	sp = (*n);
	if (str[*n] && (str[*n] == '$' || str[*n] == '?'))
	{
		; // handle pid and exit code expansion
	}
	else
	{
		while (str[*n] && ft_isalnum(str[*n]))
		{
			(*n)++;
			ep = *n;
		}
		temp = ft_substr(str, sp, ep - sp);
		expansion = get_env(temp, m->env);
		free(temp);
		if (expansion == NULL)
			return (1);
		array = ft_split(expansion, ' ');
		sp = *n;
		while (str[*n])
		{
			(*n)++;
			ep = (*n);
		}
		merge_arrays(&(cmd->args), array, i);
		append_array(&(cmd->args), ft_substr(str, sp, ep - sp));
	}
	return (0);
}

void	merge_arrays(char ***array1, char **array2, int *i)
{
	char	**new_array;
	int	size1;
	int	size2;
	int	j;
	int	k;
	int	l;

	size1 = 0;
	size2 = 0;
	while ((*array1)[size1])
		size1++;
	while (array2[size2])
		size2++;
	new_array = malloc(sizeof(char *) * (size1 + size2));
	j = 0;
	l = (*i);
	while (j < l)
	{
		new_array[j] = (*array1)[j];
		j++;
	}
	k = 0;
	while (array2[k])
	{
		new_array[j] = array2[k];
		k++;
		j++;
	}
	l++;
	j--;
	while ((*array1)[l])
	{
		new_array[j] = (*array1)[l];
		l++;
	}
	new_array[size1 + size2] = NULL;
	j = 0;
	// free(*array1);
	(*i) = (*i) + size2 - 1;
	*array1 = new_array;
}

void	append_array(char ***array, char *str)
{
	int		size;
	char	**new_array;
	int		i;

	size = 0;
	while ((*array)[size])
		size++;
	new_array = malloc(sizeof(char *) * size + 1);
	i = 0;
	while (i < size)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	// free(*array);
	*array = new_array;
}
