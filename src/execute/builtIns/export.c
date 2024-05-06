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


// static void	printexport(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		ft_putstr_fd("declare -x ", STDIN_FILENO);
// 		ft_putstr_fd(env[i], STDIN_FILENO);
// 		write(STDOUT_FILENO, "\n", 1);
// 		i++;
// 	}
// }

static void	printexport(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
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
	while (str[i] != '\0')
	{
		if (str[0] >= '0' && str[0] <= '9')
			return (0);
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z'))
			return (0);
	i++;
	}
	return (1);
}

void	export(t_mini *mini, t_cmds *cmds)
{
	int i;
	int res;

	res = 0;
	i = 0;
	if (ft_dstrlen(cmds->args) == 1)
		printexport(mini->env);
	else {
		while (cmds->args[++i]) {
			remove_char(cmds->args[i], '\'');
			if (isvalidenv(ft_strtok(cmds->args[i], '=')) == 0)
			{
				ft_iderr("export", cmds->args[i]);
				mini->exit_code = 1;
			}
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