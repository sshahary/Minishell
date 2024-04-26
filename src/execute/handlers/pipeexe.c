/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 03:23:24 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/25 15:04:03 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	child_process(t_mini *mini)
{
	int		res;
	char	*path;

	res = 0;
	path = find_command_path(mini->cmds->args[0], mini->env);
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
	if (check_builtin(mini->cmds->args) == 1)
		builtin(mini);
	else
		(res = execve(path, mini->cmds->args, mini->env));
	if (res == -1)
		ft_execute_err_1(mini->cmds->args[0], "command not found");
	exit(res);
}
