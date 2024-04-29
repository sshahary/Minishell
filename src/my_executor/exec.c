/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/29 12:53:42 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void	executor(t_mini *mini)
{
	if (count_cmds(mini->cmds) == 1)
	{
		handle_single_cmd(mini);
	}
	else
	{
		;//multiple  commands
	}
}

int count_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	handle_single_cmd(t_mini *mini)
{
	int pid;
	int	status;
	pid = fork();
	if (!pid)
		execve(find_path(mini, mini->cmds->commad), mini->cmds->args, mini->env);
	waitpid(pid, &status, 0);
	mini->exit_code = WEXITSTATUS(status);
}

char	*find_path(t_mini *mini, char *cmd)
{
	char *path;
	char **all_path;
	char *temp;
	char	*new_cmd;
	int	i;

	i = 0;
	path = get_env("PATH", mini->env);
	all_path = ft_split(path, ':');
	temp = ft_strjoin("/", cmd);
	while (all_path[i])
	{
		new_cmd = ft_strjoin(all_path[i], temp);
		if (access(new_cmd, X_OK) == 0)
			break;
		i++;
		free(new_cmd);
	}
	free(temp);
	if (!all_path[i])
	{
		printf("command not found\n");
		exit(127);
	}
	return (new_cmd);
}