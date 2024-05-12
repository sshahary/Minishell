/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multihandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:05:06 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/13 00:56:34 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_multiple_cmds(t_mini *mini)
{
	int	n_cmds;
	int	**fds;
	int i;

	i = 0;
	n_cmds = count_cmds(mini->cmds);
	if (!initialize_fds(&fds, n_cmds))
		return ;
	mini->pids = malloc(sizeof(pid_t) * n_cmds);
	if (!mini->pids)
	{
		free(fds);
		return ;
	}
	fork_process(mini, n_cmds, fds);
	close_fds(fds, n_cmds);
	wait_pids(mini, n_cmds);
	free(mini->pids);
	while (i < n_cmds)
	{
		free(fds[i]);
		i++;
	}
	free(fds);
}

void	fork_process(t_mini *mini, int n_cmds, int **fds)
{
	t_cmds	*cmds;
	int		i;

	i = 0;
	cmds = mini->cmds;
	while (i < n_cmds)
	{
		fork_child_proccess(mini, cmds, i, fds);
		if (cmds->next)
			cmds = cmds->next;
		i++;
	}
}

void	fork_child_proccess(t_mini *mini, t_cmds *cmds, int i, int **fds)
{
	int	fd_1;
	int	fd_2;

	fd_1 = cmds->fd_in;
	fd_2 = cmds->fd_out;
	g_sig = 1;
	mini->pids[i] = fork();
	if (mini->pids[i] == -1)
	{
		ft_putendl_fd("Fork Error", 2);
		exit(EXIT_FAILURE);
	}
	if (mini->pids[i] == 0)
	{
		if (!cmds->args)
			exit(1);
		execute_pipe_cmd(mini, i, cmds, fds);
		setup_child_process(mini, cmds, fd_1, fd_2);
		if (builtin_check_and_run(mini, cmds))
			exit(EXIT_SUCCESS);
		execve(find_path(mini, cmds->args[0]), cmds->args, mini->env);
	}
}

void	execute_pipe_cmd(t_mini *mini, int i, t_cmds *cmd, int **fd)
{
	(void)cmd;
	if (i == 0)
	{
		dup2(fd[i][1], STDOUT_FILENO);
	}
	else if (i == count_cmds(mini->cmds) - 1)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	}
	close_fds(fd, count_cmds(mini->cmds));
}

void	setup_child_process(t_mini *mini, t_cmds *cmds, int fd_1, int fd_2)
{
	(void)mini;
	if (STDIN_FILENO != cmds->fd_in)
	{
		dup2(fd_1, STDIN_FILENO);
		close (cmds->fd_in);
	}
	if (STDOUT_FILENO != cmds->fd_out)
	{
		dup2(fd_2, STDOUT_FILENO);
		close (cmds->fd_out);
	}
}
