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


static void	printexport(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		ft_putstr_fd("declare -x ", STDIN_FILENO);
		ft_putstr_fd(mini->env[i], STDIN_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

static void	addexport(char *path, char **new, int i)
{
	new[i] = ft_strdup(path);
	new[i + 1] = NULL;
}

// Get the index of first occurrance of character c
// Return NULL if not found
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

	if (path[0] == '=' || path[0] == '\0' || ft_strlen(path) == 1)
		return (-1);
	i = -1;
	while ((*env)[++i] != NULL)
	{
		// printf("Checking env[%d]: %s\n", i, (*env)[i]);
		if (!ft_strncmp((*env)[i], path, str_index_of(path, '=')))
		{
			// printf("Found matching path: %s\n", (*env)[i]);
			// printf("Replacing with: %s\n", path);
			(*env)[i] = ft_strdup(path);
			// printf("Updated env[%d]: %s\n", i, (*env)[i]);
			return (1);
		}
	}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (-1);
	i = -1;
	while ((*env)[++i])
		new[i] = ft_strdup((*env)[i]);
	addexport(path, new, i);
	*env = new;
	return (1);
}

int		isvalidnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

// void	export(char **cmds, t_mini *mini)
void	export(t_mini *mini, t_cmds *cmds)
{
	int		i;
	int		res;
	char 	**tmp;

	res = 0;
	i = -1;
	tmp = cmds->args;
	if (ft_dstrlen(cmds->args) == 1)
		printexport(mini);
	else
	{
		remove_char(cmds->args[1], '\'');
		while (cmds->args[++i])
		{
			if (isvalidnum(ft_strtok(tmp[i], '=')) == 0)
			{
				ft_iderr("export", tmp[i]);
				mini->exit_code = 1;
			}
			remove_char(cmds->args[i], '$');
			res = checkexport(cmds->args[i], &(mini->env));
		}
	}
	if (res != 1)
		mini->exit_code = 1;
}
