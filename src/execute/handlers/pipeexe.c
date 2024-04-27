/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 03:23:24 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/27 16:04:02 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


int	parent_process(t_mini *mini, pid_t pid)
{
	close(mini->fds[1]);
	waitpid(pid, NULL, 0);
	if (mini->cmds->fd_out == -1)
		return (mini->fds[0]);
	return (mini->cmds->fd_out);
}

void	child_process(t_mini *mini)
{
	int		res;
	char	*path;

	res = 0;
	path = find_command_path(mini->cmds->args[0], mini->env);
	close(mini->fds[0]);
	dup2(mini->cmds->fd_in, STDIN_FILENO);
	if (mini->cmds->fd_out == -1)
	{
		if (dup2(mini->fds[1], STDOUT_FILENO) == -1)
			ft_exit("redrecting command output to pipe");
	}
	else
	{
		if (dup2(mini->cmds->fd_out, STDOUT_FILENO) == -1)
			ft_exit("redrecting command output to pipe");
	}
	close(mini->cmds->fd_in);
	close(mini->fds[1]);
	// execve(path, mini->cmds->args, NULL);
	// if (check_builtin(mini->cmds->args) == 1)
	// 	builtin(mini);
	// else
	res = execve(path, mini->cmds->args, mini->env);
	if (res == -1)
		ft_execute_err_1(mini->cmds->args[0], "command not found");
	exit(res);
}
