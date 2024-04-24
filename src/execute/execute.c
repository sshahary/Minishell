/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/24 01:33:33 by sshahary         ###   ########.fr       */
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


static int			check_builtin(char **cmdline)
{
	char	*builtin;

	builtin = cmdline[0];
	if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo")
	|| !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env")
	|| !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export")
	|| !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit"))
		return (1);
	return (0);
}

int			builtin(t_mini	*mini)
{
	char	*builtin;

	builtin = mini->cmds->commad;
	if (!ft_strcmp(builtin, "cd"))
		cd(mini->cmds->commad, mini->env);
	else if (!ft_strcmp(builtin, "echo"))
		echo(mini->cmds->commad, mini->env);
	else if (!ft_strcmp(builtin, "pwd"))
		pwd();
	else if (!ft_strcmp(builtin, "env"))
		env(mini->env);
	else if (!ft_strcmp(builtin, "export"))
		export(mini, mini->cmds->commad);
	else if (!ft_strcmp(builtin, "unset"))
		unset(mini, mini->cmds->commad);
	else if (!ft_strcmp(builtin, "exit"))
		exit(mini, mini->cmds->commad);
	else
		return (0);
	return (1);
}


// char	**execute(t_mini *mini)
// {
// 	int	i;

// 	i = 0;
// 	if (!mini->cmds->args)
// 		return (mini->env);
// 	builtin(mini);
// 	if (access(mini->cmds->args[0], F_OK) != -1)
// 		pipex(mini);
// 	else
// 		find_command_path(mini->cmds->commad, mini->cmds->args);
// 	return (mini->env);
// }

static void	free_cmdline(void *ptr)
{
	free(ptr);
}

void		execute(t_mini *mini)
{
	mini->list = mini->list->next;
	while (mini->list != NULL)
	{
		mini->cmds = mini->list->content;
		if (mini->cmds->args[0])
		{
			// if (mini->redir == 1 && mini->flag == 0)
			// {
			// 	exec_redir(mini, mini->cmds->commands);
			// 	break ;
			// }
			if ((check_builtin(mini->cmds->args) == TRUE) && mini->flag == 0)
				builtin(mini);
			else
				pipex(mini);
		}
		mini->list = mini->list->next;
	}
	ft_lstclear(mini, free_cmdline);
}