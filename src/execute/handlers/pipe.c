/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/21 13:23:41 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char	*find_command_path(char *name, char **env)
{
	int		i;
	char	*str;
	char	**path;
	char	*pathstr;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
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

int	pipex(t_mini *mini, char *exe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		printf("exe = %s\n", exe);
		printf("cmds->comand %s\n", mini->cmds->commad);
		printf("");
		if (execve(exe, mini->cmds->args, mini->env) == -1)
			ft_error("permission denied", mini->cmds->commad, 1);
	}
	else if (pid < 0)
		ft_error("failed to fork", mini->cmds->commad, 1);
	else
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status)) // checks if the 	CHILD process terminated normally
			mini->exit_code = WEXITSTATUS(status);

	return (mini->exit_code);
}
