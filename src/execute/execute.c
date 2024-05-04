/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/04 14:39:28 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void ctrl_c_handler(int signum) {
// 	printf("\nCtrl+C pressed, quitting...\n");
// 	exit(0);
// }

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

// int	builtin(t_mini	*mini, t_cmds *cmds)
// {
// 	char	*builtin;

// 	builtin = cmds->args[0];
// 	if (!ft_strcmp(builtin, "env"))
// 		env(mini);
	// else if (!ft_strcmp(builtin, "cd"))
	// 	cd(mini);
	// else if (!ft_strcmp(builtin, "env"))
	// 	env(mini);
	// else if (!ft_strcmp(builtin, "pwd"))
	// 	pwd(mini);
	// else if (!ft_strcmp(builtin, "export"))
	// 	export(mini);
	// else if (!ft_strcmp(builtin, "unset"))
	// 	unset(mini);
	// else if (!ft_strcmp(builtin, "exit"))
	// 	mini_exit(mini);
// 	else
// 		return (0);
// 	return (1);
// }

void	execute(t_mini *mini)
{
	
	executor(mini);
}

