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

// static int	cdhome(char *path, char **cmds, char **env)s
static int	cdhome(char *path, t_mini *mini)
{

	// if (mini->cmds->args[1] == NULL || mini->cmds->args[1][1] == '~')
	// {
	// 	// ft_execute_err_2("cd", mini->cmds->args[1], "No such file or directory");
	// 	mini->exit_code = 1;
	// }
	// if (mini->cmds->args[1][1] != '~')
	// {
	// 	ft_execute_err_2("cd", mini->cmds->args[1], "No such file or directory");
	// 	mini->exit_code = 1;
	// }
	path = get_path_value("HOME", mini->env);
	if (chdir(path) == -1)
		ft_execute_err_1("cd", "HOME not set");
	return (1);
}

// static int			cdenv(char *path, char **cmds, char **env)
static int			cdenv(char *path, t_mini *mini, t_cmds *cmds)
{
	if (cmds->args[1] == NULL)
		return (1);
	path = get_path_value(&(cmds->args[1][1]), mini->env);
	if (chdir(path) == -1)
		chdir(get_path_value("HOME", mini->env));
	return (1);
}


// static void		setoldpwd(char **env)
static void		setoldpwd(t_mini *mini)
{
	char	*current;
	char	*old;
	char	tmp[MAX_PATH_LENGTH];

	// tmp = malloc(sizeof(char) * MAX_PATH_LENGTH);
	current = ft_strjoin("PWD=", getcwd(tmp, MAX_PATH_LENGTH));
	old = ft_strjoin("OLDPWD=", get_path_value("PWD", mini->env));
	checkexport(current, &mini->env);
	checkexport(old, &mini->env);
	free(current);
	free(old);			//check for free later
}

// void	cd(char **args, char **env)
void	cd(t_mini *mini, t_cmds *cmds)
{
	char	*path;
	int		res;

	path = 0;
	res = 0;
	if (cmds->args[1] != NULL && mini->cmds->args[1][0] != '~' && cmds->args[1][0] != '$')
	{
		path = cmds->args[1];
		if (chdir(path) == -1)
			res = ft_execute_err_2("cd", path, strerror(errno));
		setoldpwd(mini);
	}
	else if (cmds->args[1] == NULL || cmds->args[1][0] == '~')
		cdhome(path, mini);
	else if (cmds->args[1][0] == '$')
		cdenv(path, mini, cmds);
	if (res == -1)
		mini->exit_code = 1;
	else
		mini->exit_code = 0;
}

//tests
