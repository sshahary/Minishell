/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:31:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/22 11:31:45 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	isvalidenv(char *name)
{
	int	i;

	i = 0;
	if (name[0] >= '0' && name[0] <= '9')
		return (0);
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			;
		else
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int	checkequal(char *str, char *env)
{
	int	i;

	i = 0;
	while (str[i] && env[i] && (str[i] == env[i]) && (env[i] != '='))
		i++;
	if ((str[i] == '\0') && (env[i] == '=' || env[i] == '\0'))
		return (1);
	return (0);
}

int	envunset(char *str, char **env)
{
	int	i;
	int	j;

	j = 0;
	while (((env)[j]) != NULL)
		j++;
	if (j < 1)
		return (-1);
	i = -1;
	while ((env)[++i] != NULL)
	{
		if (checkequal(str, (env)[i]))
		{
			// free((env)[i]);
			(env)[i] = ft_strdup((env)[j - 1]);
			// free((env)[j - 1]);
			(env)[j - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

void	unset(t_mini *mini, t_cmds *cmds)
{
	int	res;
	int	i;

	res = 0;
	i = 1;
	while (cmds->args[i])
	{
		if (isvalidenv(cmds->args[i]))
		{
			if (envunset(cmds->args[i], (mini->env)))
				return ;
			else
				res = 1;
		}
		else
			res = 1;
		i++;
	}
	if (res != 0)
		mini->exit_code = 1;
}
