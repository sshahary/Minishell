/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:17:07 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/20 22:47:51 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


static int	cdhome(char *path, char **cmds, char **env)
{
	t_mini	*mini;

	if (cmds[1][1] == '~')
	{
		ft_execute_err_2("cd", cmds[1], "No such file or directory");
		mini->exit_code = 1;
	}
	path = find_command_path("HOME", env);
	if (chdir(path) == -1)
		ft_execute_err_1("cd", "HOME not set");
	return (1);
}

static int			cdenv(char *path, char **cmds, char **env)
{
	path = find_command_path(&(cmds[1][1]), env);
	if (chdir(path) == -1)
		chdir(find_command_path("HOME", env));
	return (1);
}

static void		setoldpwd(char **env)
{
	char	*cur;
	char	*old;
	char	*tmp;

	tmp = malloc(sizeof(char) * MAX_PATH_LENGTH);
	cur = ft_strjoin("PWD=", getcwd(tmp, MAX_PATH_LENGTH));
	old = ft_strjoin("OLDPWD=", find_command_path("PWD", env));
	checkexport(cur, &env);
	checkexport(old, &env);
	// free(cur);
	// free(old);			//check for free later
}

void	cd(char **args, char **env)
{
	char	*path;
	int		res;
	t_mini	*mini;

	path = 0;
	res = 0;
	if (args[1] != NULL && args[1][0] != '~' && args[1][0] != '$')
	{
		path = args[1];
		if (chdir(path) == -1)
			res = ft_execute_err_2("cd", path, strerror(errno));
		setoldpwd(env);
	}
	else if (args[1] == NULL || args[1][0] == '~')
		cdhome(path, args, env);
	else if (args[1][0] == '$')
		cdenv(path, args, env);
	if (res == -1)
		mini->exit_code = 1;
	else
		mini->exit_code = 0;
}
