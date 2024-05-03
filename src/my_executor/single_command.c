/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/03 14:19:21 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_single_cmd(t_mini *mini)
{
	int	pid;
	int	status;

	if (builtin_check_and_run(mini, mini->cmds))
		return ;
	pid = fork();
	if (!pid)
	{
		if (STDIN_FILENO != mini->cmds->fd_in)
			dup2(mini->cmds->fd_in, STDIN_FILENO);
		if (STDOUT_FILENO != mini->cmds->fd_out)
			dup2(mini->cmds->fd_out, STDOUT_FILENO);
		execve(find_path(mini, mini->cmds->args[0]), mini->cmds->args, \
		mini->env);
	}
	waitpid(pid, &status, 0);
	mini->exit_code = WEXITSTATUS(status);
}
