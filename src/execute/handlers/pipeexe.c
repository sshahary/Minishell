/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 03:23:24 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/28 04:45:33 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


// int	parent_process(t_mini *mini, pid_t pid)
// {
// 	close(mini->fds[1]);
// 	waitpid(pid, NULL, 0);
// 	if (mini->cmds->fd_out == -1)
// 		return (mini->fds[0]);
// 	return (mini->cmds->fd_out);
// }

// void	child_process(t_mini *mini)
// {
// 	int		res;
// 	char	*path;

// 	res = 0;
// 	path = find_command_path(mini->cmds->args[0], mini->env);
// 	close(mini->fds[0]);
// 	dup2(mini->cmds->fd_in, STDIN_FILENO);
// 	if (mini->cmds->fd_out == -1)
// 	{
// 		if (dup2(mini->fds[1], STDOUT_FILENO) == -1)
// 			ft_exit("redrecting command output to pipe");
// 	}
// 	else
// 	{
// 		if (dup2(mini->cmds->fd_out, STDOUT_FILENO) == -1)
// 			ft_exit("redrecting command output to pipe");
// 	}
// 	close(mini->cmds->fd_in);
// 	close(mini->fds[1]);
// 	// execve(path, mini->cmds->args, NULL);
// 	// if (check_builtin(mini->cmds->args) == 1)
// 	// 	builtin(mini);
// 	// else
// 	res = execve(path, mini->cmds->args, mini->env);
// 	if (res == -1)
// 		ft_execute_err_1(mini->cmds->args[0], "command not found");
// 	exit(res);
// }

void	child_process(t_cmds *cmd, t_mini *mini)
{
	int		ret;
	char	*path;

	ret = 0;
	path = find_command_path(cmd->args[0], mini->env);
	if (mini->flag == 1)
	{
		dup2(mini->fds[1], STDOUT_FILENO);
		close(mini->fds[1]);
	}
	if (mini->fds[0] != 0)
	{
		dup2(mini->fds[0], STDIN_FILENO);
		close(mini->fds[0]);
	}
	if (check_builtin(cmd->args) == 1)
		builtin(mini);
	else
		(ret = execve(path, cmd->args, mini->env));
	if (ret == -1)
		ft_execute_err_1(cmd->args[0], "command not found");
	exit(ret);
}