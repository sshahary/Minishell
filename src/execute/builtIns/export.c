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

// static void updateexport(char *name, char *value, char **env)
// {
// 	int i = 0;
// 	char *variable = ft_strjoin(name, "=");
// 	char *new_entry = ft_strjoin(variable, value);
// 	free(variable);

// 	while (env[i] != NULL)
// 	{
// 		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
// 		{
// 			free(env[i]);
// 			env[i] = new_entry;
// 			return;
// 		}
// 		i++;
// 	}
// }
// void	export(char **cmds, t_mini *mini)
void	export(t_mini *mini)
{
	int		i;
	int		res;
	char 	**tmp;

	res = 0;
	i = 0;
	tmp = mini->cmds->args;
	if (ft_dstrlen(mini->cmds->args) == 1)
		printexport(mini);
	else
	{
		remove_char(mini->cmds->args[1], '\'');
		while (mini->cmds->args[++i])
		{
			if (isvalidnum(ft_strtok(tmp[i], '=')) == 0)
			{
				ft_iderr("export", tmp[i]);
				mini->exit_code = 1;
			}
			remove_char(mini->cmds->args[i], '$');
			res = checkexport(mini->cmds->args[i], &(mini->env));
		}
	}
	if (res != 1)
		mini->exit_code = 1;
}
