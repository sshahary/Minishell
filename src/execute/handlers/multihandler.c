/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multihandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:05:06 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/09 22:27:54 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_multiple_cmds(t_mini *mini)
{
	int	n_cmds;
	int	**fds;

	n_cmds = count_cmds(mini->cmds);
	if (!initialize_fds(&fds, n_cmds))
		return ;
	mini->pids = malloc(sizeof(pid_t) * n_cmds);
	if (!mini->pids)
		return ;
	fork_process(mini, n_cmds, fds);
	close_fds(fds, n_cmds);
	wait_pids(mini, n_cmds);
}

void	fork_process(t_mini *mini, int n_cmds, int **fds)
{
	t_cmds	*cmds;
	int		i;
	int		fd[2];

	i = 0;
	cmds = mini->cmds;
	while (i < n_cmds)
	{
		fork_child_proccess(mini, cmds, i, fds, fd);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		if (cmds->next)
			cmds = cmds->next;
		i++;
	}
}

void	fork_child_proccess(t_mini *mini, t_cmds *cmds, int i, int **fds, int *fd)
{
	int	fd_1;
	int	fd_2;

	fd_1 = cmds->fd_in;
	fd_2 = cmds->fd_out;
	mini->pids[i] = fork();
	if (mini->pids[i] == -1)
	{
		ft_putendl_fd("Fork Error", 2);
		exit(EXIT_FAILURE);
	}
	if (mini->pids[i] == 0)
	{
		execute_pipe_cmd(mini, i, cmds, fds);
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
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
	if (STDIN_FILENO != mini->cmds->fd_in)
	{
		dup2(fd_1, STDIN_FILENO);
		close (cmds->fd_in);
	}
	if (STDOUT_FILENO != mini->cmds->fd_out)
	{
		dup2(fd_2, STDOUT_FILENO);
		close (cmds->fd_out);
	}
}
