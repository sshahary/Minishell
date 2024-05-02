/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/01 11:08:15 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


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

void		status_child(pid_t pid, t_mini *mini)
{
	if (WIFEXITED(pid))
		mini->exit_code = WEXITSTATUS(pid);
	if (WIFSIGNALED(pid))
	{
		mini->exit_code = WTERMSIG(pid);
		if (mini->exit_code != 131)
			mini->exit_code += 128;
	}
}

int		pipex(t_cmds *cmd, t_mini *mini)
{
	pid_t	pid;
	int		ret;
	// int		status;
	t_cmds	*next_cmd;
	char	*path;

	ret = EXIT_SUCCESS;
	path = find_command_path(cmd->args[0], mini->env);
	next_cmd = cmd;
	if (mini->flag == 1)
	{
		next_cmd = cmd->next;
		mini->preflag = 1;
		pipe(mini->fds);
	}
	pid = fork();
	if (pid == 0)
		child_process(cmd, mini);
	waitpid(pid, &mini->exit_code, 0);
	if (mini->flag == 1)
		close(mini->fds[1]);
	if (mini->fds[0] != 0)
		close(mini->fds[0]);
	status_child(pid, mini);

	return (ret);
}