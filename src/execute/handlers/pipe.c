/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/27 15:51:00 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char	*find_command_path(char *name, char **env)
{
	// struct	stat s;
	int		i;
	char	*str;
	char	**path;
	char	*pathstr;

	i = 0;
	// printf("GET_ENV: %s\n", get_env("PATH", env));
	while (env[i] && ft_strcmp(env[i], "PATH="))
		i++;
	if (!(env[i]))
		return (name);
	path = ft_split(pathstr, ':');
	i = 0;
	while (path && path[i])
	{
		str = strjoinslash(path[i], name);
		if (!(access(str, F_OK)))
		{
			ft_pfree((void **)path);
			return (str);
		}
		free(str);
		i++;
	}
	ft_pfree((void **)path);
	return (name);
}

// char	*find_command_path(char *name, char **env)
// {
// 	int		i;
// 	char	*str;
// 	char	**path;
// 	char	*pathstr;

// 	i = 0;
// 	while (env[i] && ft_strcmp(env[i], "PATH="))
// 		i++;
// 	if (!(env[i]))
// 		return (name);
// 	path = ft_split(pathstr, ':');
// 	i = 0;
// 	while (path && path[i])
// 	{
// 		str = strjoinslash(path[i], name);
// 		if (!(access(str, F_OK)))
// 		{
// 			ft_pfree((void **)path);
// 			return (str);
// 		}
// 		free(str);
// 		i++;
// 	}
// 	ft_pfree((void **)path);
// 	return (name);
// }

int			pipex(t_mini *mini)
{
	pid_t	pid;
	// int		res;
	// int		status;
	// char	*path;

	// res = 0;
	// path = find_command_path(mini->cmds->args[0], mini->env);
	if (pipe(mini->fds) == -1)
		ft_exit("creating of pipe failed");
	pid = fork();
	if (pid == 0)
		child_process(mini);
	if (pid > 0)
		parent_process(mini, pid);
	else
		ft_exit("forking failed");
	return (0);
}

