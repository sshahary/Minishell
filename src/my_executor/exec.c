/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/29 17:10:36 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void	forker(t_mini *mini, int i)
{
	mini->pids[i] = fork();
}

void	exec_multi_pipe(t_mini *mini, int i, t_cmds *cmd, int *fd)
{
	if (i == 0)
		dup2(fd[0], STDIN_FILENO);
	else if (i == count_cmds(mini->cmds) - 1)
		dup2(fd[1], STDOUT_FILENO);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	execve(find_path(mini, cmd->commad), cmd->args, mini->env);
}

void	close_fds(int **fd)
{
	int i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void multi_pipes(t_mini *mini) {
    int i;
    int status[count_cmds(mini->cmds)];
    t_cmds *temp;
    int **fd;

    fd = malloc(sizeof(int *) * count_cmds(mini->cmds));
    for (i = 0; i < count_cmds(mini->cmds); i++) {
        fd[i] = malloc(sizeof(int) * 2);
        pipe(fd[i]);
    }

    mini->pids = malloc(sizeof(pid_t) * count_cmds(mini->cmds));
    temp = mini->cmds;
    for (i = 0; i < count_cmds(mini->cmds); i++) {
        mini->pids[i] = fork();
        if (mini->pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (mini->pids[i] == 0) { // Child process
            exec_multi_pipe(mini, i, temp, fd[i]);
            exit(EXIT_SUCCESS); // Child process should exit after execution
        }
        temp = temp->next;
    }

    for (i = 0; i < count_cmds(mini->cmds); i++) {
        close(fd[i][0]);
        close(fd[i][1]);
    }

    for (i = 0; i < count_cmds(mini->cmds); i++) {
        if (waitpid(mini->pids[i], &status[i], 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }

    // Set exit code based on the last process status
    mini->exit_code = WEXITSTATUS(status[count_cmds(mini->cmds) - 1]);
}


void	executor(t_mini *mini)
{
	if (count_cmds(mini->cmds) == 1)
	{
		handle_single_cmd(mini);
	}
	else
	{
		multi_pipes(mini);//multiple  commands
	}
}

int count_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	handle_single_cmd(t_mini *mini)
{
	int pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		if (STDIN_FILENO != mini->cmds->fd_in)
			dup2(mini->cmds->fd_in, STDIN_FILENO);
		if (STDOUT_FILENO != mini->cmds->fd_out)
			dup2(mini->cmds->fd_out, STDOUT_FILENO);
		execve(find_path(mini, mini->cmds->commad), mini->cmds->args, mini->env);
	}
	waitpid(pid, &status, 0);
	mini->exit_code = WEXITSTATUS(status);
}

char	*find_path(t_mini *mini, char *cmd)
{
	char	*path;
	char	**all_path;
	char	*temp;
	char	*new_cmd;
	int		i;

	i = 0;
	path = get_env("PATH", mini->env);
	all_path = ft_split(path, ':');
	temp = ft_strjoin("/", cmd);
	while (all_path[i])
	{
		new_cmd = ft_strjoin(all_path[i], temp);
		if (access(new_cmd, X_OK) == 0)
			break;
		i++;
		free(new_cmd);
	}
	free(temp);
	if (!all_path[i])
	{
		printf("command not found\n");
		exit(127);
	}
	return (new_cmd);
}
