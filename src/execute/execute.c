/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/12 21:21:37 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_check_and_run(t_mini *mini, t_cmds *cmd)
{
	char	*builtin;

	builtin = cmd->args[0];
	if (!ft_strcmp(builtin, "echo"))
		echo(cmd, mini);
	else if (!ft_strcmp(builtin, "cd"))
		cd(mini, cmd);
	else if (!ft_strcmp(builtin, "env"))
		env(mini, cmd);
	else if (!ft_strcmp(builtin, "pwd"))
		pwd(mini);
	else if (!ft_strcmp(builtin, "export"))
		export(mini, cmd);
	else if (!ft_strcmp(builtin, "unset"))
		unset(mini, cmd);
	else if (!ft_strcmp(builtin, "exit"))
		mini_exit(mini, cmd);
	else
		return (0);
	return (1);
}

void	executor(t_mini *mini)
{
	if (count_cmds(mini->cmds) == 1)
	{
		handle_single_cmd(mini);
	}
	else
	{
		handle_multiple_cmds(mini);
	}
}
