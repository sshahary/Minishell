/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check_and_run.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:06 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/03 18:27:07 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_check_and_run(t_mini *mini, t_cmds *cmd)
{
	char	*builtin;

	(void) mini;

	builtin = cmd->args[0];
	if (!ft_strcmp(builtin, "echo"))
		echo(cmd);
	else if (!ft_strcmp(builtin, "cd"))
		cd(mini, cmd);
	else if (!ft_strcmp(builtin, "env"))
		env(mini);
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