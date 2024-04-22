/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/22 04:07:54 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void ctrl_c_handler(int signum) {
// 	printf("\nCtrl+C pressed, quitting...\n");
// 	exit(0);
// }

//  void	builtin(t_mini *mini)
// {
// 	if (ft_strncmp(&mini->cmds->commad[0], "echo", 4))
// 		echo(mini->cmds->args);
// 	// else if (ft_strncmp(cmd[0], "cd", 2))
// 	// 	cd(cmd[1]);
// 	// else if (ft_strncmp(cmd[0], "env", 3))
// 	// 	env(shell.env, 0);
// 	// else if (ft_strncmp(cmd[0], "pwd", 3))
// 	// 	pwd();
// 	// else if (ft_strncmp(cmd[0], "unset", 5))
// 	// 	unset(shell.env, cmd[0]);
// 	// else if (ft_strncmp(cmd[0], "export", 6))
// 	// 	export(shell.env, cmd[0]);
// 	else
// 		ft_error(*(mini->env),"command not found", 127);
// }

int			exec_builtin(t_mini	*mini)
{
	char	*builtin;

	builtin = mini->cmds->commands[0];
	if (!ft_strcmp(builtin, "cd"))
		ft_cd(mini->cmds->commands, mini->env);
	else if (!ft_strcmp(builtin, "echo"))
		ft_echo(mini->cmds->commands, mini->env);
	else if (!ft_strcmp(builtin, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(builtin, "env"))
		ft_env(mini->env);
	else if (!ft_strcmp(builtin, "export"))
		ft_export(mini, mini->cmds->commands);
	else if (!ft_strcmp(builtin, "unset"))
		ft_unset(mini, mini->cmds->commands);
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit(mini, mini->cmds->commands);
	else
		return (0);
	return (1);
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