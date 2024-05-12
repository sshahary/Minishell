/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:47:56 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/20 22:50:41 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	printexport(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

static void	addexport(char *path, char **new, int i)
{
	new[i] = ft_strdup(path);
	new[i + 1] = NULL;
}

static int	str_index_of(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

int	checkexport(char *path, char ***env)
{
	int		i;
	char	**new;

	if (path[0] == '=' || path[0] == '\0')
		return (-1);
	i = -1;
	while ((*env)[++i] != NULL)
	{
		if (!ft_strncmp((*env)[i], path, str_index_of(path, '=')))
		{
			(*env)[i] = ft_strdup(path);
			return (1);
		}
	}
	new = malloc(sizeof(char *) * (i + 2));
	if (!(new))
		return (-1);
	i = -1;
	while ((*env)[++i])
		new[i] = ft_strdup((*env)[i]);
	addexport(path, new, i);
	*env = new;
	return (1);
}

void	export(t_mini *mini, t_cmds *cmds)
{
	int	i;
	int	res;
	char	*token;

	res = 0;
	i = 0;
	if (ft_dstrlen(cmds->args) == 1)
		printexport(mini->env);
	else
	{
		while (cmds->args[++i])
		{
			token = ft_strtok(cmds->args[i], '=');
			if (token == NULL || token[0] == '\0')
			{
				ft_iderr("export", cmds->args[i], mini->exit_code);
				continue ;
			}
			if (isvalidenv(token) == 0)
				ft_iderr("export", cmds->args[i], mini->exit_code);
			else
			{
				remove_char(cmds->args[i], '_');
				res = checkexport(cmds->args[i], &(mini->env));
			}
		}
	}
	if (res != 1)
		mini->exit_code = 1;
}
