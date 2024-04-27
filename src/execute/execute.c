/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:36:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/27 16:05:12 by sshahary         ###   ########.fr       */
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
	|| !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export")
	|| !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit"))
		return (1);
	return (0);
}

int	builtin(t_mini	*mini)
{
	char	*builtin;

	builtin = mini->cmds->commad;
	if (!ft_strcmp(builtin, "echo"))
		echo(mini);
	else if (!ft_strcmp(builtin, "cd"))
		cd(mini);
	else if (!ft_strcmp(builtin, "env"))
		env(mini);
	else if (!ft_strcmp(builtin, "pwd"))
		pwd(mini);
	else if (!ft_strcmp(builtin, "export"))
		export(mini);
	else if (!ft_strcmp(builtin, "unset"))
		unset(mini);
	else if (!ft_strcmp(builtin, "exit"))
		mini_exit(mini);
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
// 	// if ((check_builtin(mini->cmds->args) == 1) && mini->flag == 0)
// 	builtin(mini);
// 	// else
// 	// 	pipex(mini);
// 	if (access(mini->cmds->args[0], F_OK) != -1)
// 		pipex(mini);
// 	else
// 		find_command_path(mini->cmds->commad, mini->cmds->args);
// 	// builtin(mini);
// 	return (mini->env);
// }

// static void	free_cmdline(void *ptr)
// {
// 	free(ptr);
// }

// void		execute(t_mini *mini)
// {
// 	mini->list = mini->cmds->next;
// 	while (mini->cmds != NULL)
// 	{
// 		mini->cmds = mini->cmds->args;
// 		if (mini->cmds->args[0])
// 		{
// 			if ((check_builtin(mini->cmds->args) == 1) && mini->flag == 0)
// 				builtin(mini);
// 			else
// 				pipex(mini);
// 		}
// 		mini->cmds = mini->cmds->next;
// 	}
// 	// ft_lstclear(mini->env, free_cmdline);
// }

// void	execute(t_mini *mini)
// {
// 	int		i;
// 	char	**len;

// 	len = mini->cmds->args;
// 	i = 0;
// 	while 
// 	if (mini->cmds->args[0])
// 	{
// 		if ((check_builtin(mini->cmds->args) == 1) && mini->flag == 0)
// 			builtin(mini);
// 		else
// 			pipex(mini);
// 	}
// 	}


void	execute(t_mini *mini)
{
	// t_cmds	*cmds;

	// cmds = mini->cmds;
	// while (cmds)
	// {
		if(check_builtin(mini->cmds->args))
			builtin(mini);
		else
			pipex(mini);
		// cmds = cmds->next;
	// }
}
