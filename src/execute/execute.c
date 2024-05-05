/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/05 14:52:32 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	check_builtin(char **args)
{
	char	*builtin;

	builtin = args[0];
	if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo")
	|| !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env")
	|| !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "unset")
	|| !ft_strcmp(builtin, "exit"))
		return (1);
	return (0);
}

int	builtin_check_and_run(t_mini *mini, t_cmds *cmd)
{
	char	*builtin;

	(void) mini;

	builtin = cmd->args[0];
	if (!ft_strcmp(builtin, "echo"))
		echo(cmd, *mini);
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
