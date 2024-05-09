/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:28 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/09 16:28:54 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void handle_multiple_cmds(t_mini *mini)
{
	int n_cmds;
	int **fds;

	n_cmds = count_cmds(mini->cmds);
	if (!initialize_fds(&fds, n_cmds))
		return;
	mini->pids = malloc(sizeof(pid_t) * n_cmds);
	if (!mini->pids)
		return;
	fork_process(mini, n_cmds, fds);
	close_fds(fds, n_cmds);
	wait_pids(mini, n_cmds);
}

void fork_process(t_mini *mini, int n_cmds, int **fds)
{
	int fd_1;
	int fd_2;
	t_cmds *cmds;
	int i;
	int fd1;
	int fd2;

	i = 0;
	cmds = mini->cmds;
	while (i < n_cmds)
	{
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
			execute_pipe_cmd( mini, i, cmds, fds);
			fd1 = dup(STDIN_FILENO);
			fd2 = dup(STDOUT_FILENO);

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
			if (builtin_check_and_run(mini, cmds))
				exit(EXIT_SUCCESS);
			execve(find_path(mini, cmds->args[0]), cmds->args, mini->env);
		}

		dup2(fd1, STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		if (cmds->next)
			cmds = cmds->next;
		i++;
	}
}
void execute_pipe_cmd(t_mini *mini, int i, t_cmds *cmd, int **fd)
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
	// execve(find_path(mini, cmd->args[0]), cmd->args, mini->env);
}

void close_fds(int **fds, int n_cmds)
{
	int i;
	i = 0;
	while (i < n_cmds)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}

void wait_pids(t_mini *mini, int n_cmds)
{
	int i;
	int status;
	i = 0;
	while (i < n_cmds)
	{
		if (waitpid(mini->pids[i], &status, 0) == -1)
		{
			ft_putendl_fd("Waitpid Error", 2);
			exit(EXIT_FAILURE);
		}
		mini->exit_code = WEXITSTATUS(status);
		i++;
	}
}