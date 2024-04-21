/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/21 13:26:07 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void ctrl_c_handler(int signum) {
// 	printf("\nCtrl+C pressed, quitting...\n");
// 	exit(0);
// }

 void	builtin(t_mini *mini)
{
	if (ft_strncmp(&mini->cmds->commad[0], "echo", 4))
		echo(mini->cmds->args);
	// else if (ft_strncmp(cmd[0], "cd", 2))
	// 	cd(cmd[1]);
	// else if (ft_strncmp(cmd[0], "env", 3))
	// 	env(shell.env, 0);
	// else if (ft_strncmp(cmd[0], "pwd", 3))
	// 	pwd();
	// else if (ft_strncmp(cmd[0], "unset", 5))
	// 	unset(shell.env, cmd[0]);
	// else if (ft_strncmp(cmd[0], "export", 6))
	// 	export(shell.env, cmd[0]);
	else
		ft_error(*(mini->env),"command not found", 127);
}


char	**execute(t_mini *mini)
{
	int	i;

	i = 0;
	if (!mini->cmds->args)
		return (mini->env);
	builtin(mini);
	if (access(mini->cmds->args[0], F_OK) != -1)
		pipex(mini, mini->cmds->args[0]);
	else
		find_command_path(mini->cmds->commad, mini->cmds->args);
	return (mini->env);
}