/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:46:18 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/26 11:46:53 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0' && j < n)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

int	handle_pid_exitcode_expansion(char *str, int *i, char **ex_str, t_mini *m)
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
		printf("Command: %s\t FD_IN: %d  FD_OUT: %d\n", temp->commad, temp->fd_in, temp->fd_out);
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
			return (&(env[i][name_len + 1]));
		}
		i++;
	}
	return (NULL);
}
