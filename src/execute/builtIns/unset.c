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

int		checkequal(char *str, char *env)
{
	int	i;

	i = 0;
	while (str[i] && env[i] && (str[i] == env[i]) && (env[i] != '='))
		i++;
	if ((str[i] == '\0') && (env[i] == '='))
		return (1);
	return (0);
}

int		unsetenv(char *str, char ***env)
{
	int	i;
	int	j;

	j = 0;
	while (((*env)[j]) != NULL)
		j++;
	if (j < 1)
		return (-1);
	i = -1;
	while ((*env)[++i] != NULL)
	{
		if (checkequal(str, (*env)[i]))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup((*env)[j - 1]);
			free((*env)[j - 1]);
			(*env)[j - 1] = NULL;
			return (1);
		}
	}
	return (1);
}

void	unset(char **cmds, t_mini *mini)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (mini->preflag == 1)
		return ;
	while (cmds[++i])
	{
		remove_char(cmds[i], '\'');
		res = isvalidenv(cmds[i]) && unsetenv(cmds[i], &(mini->env));
	}
	if (res != 1)
		mini->exit_code = 1;
}
