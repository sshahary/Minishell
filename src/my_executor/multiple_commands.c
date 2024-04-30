/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:50 by rpambhar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/30 13:38:22 by sshahary         ###   ########.fr       */
=======
/*   Updated: 2024/04/30 14:27:31 by rpambhar         ###   ########.fr       */
>>>>>>> b2032a8cc0101eea5ebdfdf1c805d61ceb748b2e
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_multiple_cmds(t_mini *mini)
{
	int	n_cmds;
	int	**fds;

	n_cmds = count_cmds(mini->cmds);
	if (!initialize_fds(&fds, n_cmds))
<<<<<<< HEAD
		return;
=======
		return ;
>>>>>>> b2032a8cc0101eea5ebdfdf1c805d61ceb748b2e
	mini->pids = malloc(sizeof(pid_t) * n_cmds);
	if (!mini->pids)
		return ;
	fork_process(mini, n_cmds, fds);
	close_fds(fds, n_cmds);
	wait_pids(mini, n_cmds);
}

void	fork_process(t_mini *mini, int n_cmds, int **fds)
{
<<<<<<< HEAD
	t_cmds  *cmds;
	int     i;
=======
	t_cmds	*cmds;
	int		i;
>>>>>>> b2032a8cc0101eea5ebdfdf1c805d61ceb748b2e

	i = 0;
	cmds = mini->cmds;
	while (i < n_cmds)
	{
		mini->pids[i] = fork();
		if (mini->pids[i] == -1)
		{
			ft_putendl_fd("Fork Error", 2);
			exit(EXIT_FAILURE);
		}
		else if (mini->pids[i] == 0)
		{
			execute_pipe_cmd(mini, i, cmds, fds[i]);
			exit(EXIT_SUCCESS);
		}
		cmds = cmds->next;
		i++;
	}
}

void	execute_pipe_cmd(t_mini *mini, int i, t_cmds *cmd, int *fd)
{
	if (i == 0)
	{
		dup2(fd[0], STDIN_FILENO);
	}
	else if (i == count_cmds(mini->cmds) - 1)
		dup2(fd[1], STDOUT_FILENO);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	execve(find_path(mini, cmd->commad), cmd->args, mini->env);
}

void	close_fds(int **fds, int n_cmds)
{
<<<<<<< HEAD
	int i;
=======
	int	i;
>>>>>>> b2032a8cc0101eea5ebdfdf1c805d61ceb748b2e

	i = 0;
	while (i < n_cmds)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}

void	wait_pids(t_mini *mini, int n_cmds)
{
<<<<<<< HEAD
	int i;
	int status;
=======
	int	i;
	int	status;
>>>>>>> b2032a8cc0101eea5ebdfdf1c805d61ceb748b2e

	i = 0;
	while (i < n_cmds)
	{
		if (waitpid(mini->pids[i], &status, 0) == -1)
		{
			ft_putendl_fd("Waitpid Error", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	mini->exit_code = WEXITSTATUS(status);
}
