/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/09 17:33:31 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_cmds(t_cmds *cmds)
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

char	*find_path(t_mini *mini, char *cmd)
{
	char	*path;
	char	**all_path;
	char	*temp;
	char	*new_cmd;
	int		i;

	if (access (cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	path = get_env("PATH", mini->env);
	all_path = ft_split(path, ':');
	temp = ft_strjoin("/", cmd);
	while (all_path[i])
	{
		new_cmd = ft_strjoin(all_path[i], temp);
		if (access (new_cmd, X_OK) == 0)
			break ;
		i++;
		free(new_cmd);
	}
	free(temp);
	if (!all_path[i])
	{
		ft_execute_err_2(all_path[i], cmd, "command not found");
		exit(127);
	}
	return (new_cmd);
}

int	initialize_fds(int ***fds, int n_cmds)
{
	int	i;

	i = 0;
	*fds = malloc(sizeof (int *) * n_cmds);
	if (!(*fds))
		return (0);
	while (i < n_cmds)
	{
		(*fds)[i] = malloc(sizeof(int) * 2);
		if (!(*fds)[i])
			return (0);
		pipe((*fds)[i]);
		i++;
	}
	return (1);
}


//Single hand pipes

// void	handle_single_cmd(t_mini *mini)
// {
// 	int	pid;
// 	int	status;
// 	int	res;
// 	int	fd1;
// 	int	fd2;
// 	int	fd_1;
// 	int	fd_2;

// 	fd1 = dup(STDIN_FILENO);
// 	fd2 = dup(STDOUT_FILENO);
// 	fd_1 = mini->cmds->fd_in;
// 	fd_2 = mini->cmds->fd_out;



// 	if (STDIN_FILENO != mini->cmds->fd_in)
// 	{
// 		dup2(fd_1, STDIN_FILENO);
// 		close(mini->cmds->fd_in);
// 	}
// 	if (STDOUT_FILENO != mini->cmds->fd_out)
// 	{
// 		dup2(fd_2, STDOUT_FILENO);
// 		close(mini->cmds->fd_out);
// 	}
// 	if (builtin_check_and_run(mini, mini->cmds))
// 	{
// 		dup2(fd1, STDIN_FILENO);
// 		dup2(fd2, STDOUT_FILENO);
// 		return ;
// 	}
// 	res = 0;
// 	pid = fork();
// 	if (!pid)
// 	{
// 		res = execve(find_path(mini, mini->cmds->args[0]), mini->cmds->args, \
// 		mini->env);
// 	}
// 	dup2(fd1, STDIN_FILENO);
// 	dup2(fd2, STDOUT_FILENO);
// 	if (res == -1)
// 		ft_execute_err_1(mini->cmds->args[0], "command not found");
// 	waitpid(pid, &status, 0);
// 	mini->exit_code = WEXITSTATUS(status);
// }
