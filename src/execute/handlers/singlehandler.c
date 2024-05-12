/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlehandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:15:26 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/12 22:13:26 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	restore_fds(int fd1, int fd2)
{
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

static void	redirect_fds(int fd1, int fd2, t_mini *mini)
{
	if (STDIN_FILENO != mini->cmds->fd_in)
	{
		dup2(fd1, STDIN_FILENO);
		close(mini->cmds->fd_in);
	}
	if (STDOUT_FILENO != mini->cmds->fd_out)
	{
		dup2(fd2, STDOUT_FILENO);
		close(mini->cmds->fd_out);
	}
}

static void	fds_fill(int *fd, t_mini *mini)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = mini->cmds->fd_in;
	fd[3] = mini->cmds->fd_out;
}

void	handle_single_cmd(t_mini *mini)
{
	int	pid;
	int	status;
	int	res;
	int	fd[4];

	if (!mini->cmds->args)
		return ;
	if (int_strchr(mini->cmds->args[0], '/') && check_if_file_exits(mini, mini->cmds->args[0]))
		return ;
	fds_fill(fd, mini);
	redirect_fds(fd[2], fd[3], mini);
	if (builtin_check_and_run(mini, mini->cmds))
	{
		restore_fds(fd[0], fd[1]);
		return ;
	}
	res = 0;
	g_sig = 1;
	pid = fork();
	if (!pid)
	{
		if (!mini->cmds->args)
			exit(1);
		res = execve(find_path(mini, mini->cmds->args[0]), mini->cmds->args, \
		mini->env);
		if (res == -1)
		{
			ft_execute_err_1(mini->cmds->args[0], "command not found");
			exit (127);
		}
	}
	restore_fds(fd[0], fd[1]);
	waitpid(pid, &status, 0);
	mini->exit_code = WEXITSTATUS(status);
	g_sig = 0;

}
