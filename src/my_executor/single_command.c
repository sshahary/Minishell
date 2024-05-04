/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/04 17:55:14 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_single_cmd(t_mini *mini)
{
	int	pid;
	int	status;
	int	res;

	if (builtin_check_and_run(mini, mini->cmds))
		return ;
	res = 0;
	pid = fork();
	if (!pid)
	{
		if (STDIN_FILENO != mini->cmds->fd_in)
			dup2(mini->cmds->fd_in, STDIN_FILENO);
		if (STDOUT_FILENO != mini->cmds->fd_out)
			dup2(mini->cmds->fd_out, STDOUT_FILENO);
		res = execve(find_path(mini, mini->cmds->args[0]), mini->cmds->args, \
		mini->env);
	}
	if (res == -1)
		ft_execute_err_1(mini->cmds->args[0], "command not found");
	waitpid(pid, &status, 0);
	mini->exit_code = WEXITSTATUS(status);
}
