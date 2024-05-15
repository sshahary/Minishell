/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/13 01:34:01 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	path_err(char *exe1, char *exe2, char *msg)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(exe1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(exe2, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(127);
	return (-1);
}

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
	i = -1;
	path = get_env("PATH", mini->env);
	if (!path)
		path_err(path, cmd, "command not found");
	all_path = ft_split(path, ':');
	temp = ft_strjoin("/", cmd);
	while (all_path[++i])
	{
		new_cmd = ft_strjoin(all_path[i], temp);
		if (access (new_cmd, X_OK) == 0)
			break ;
		free(new_cmd);
	}
	free(temp);
	if (!all_path[i])
		path_err(all_path[i], cmd, "command not found");
	return (new_cmd);
}

int	pre_check(t_mini *mini, int *fd)
{
	if (!mini->cmds->args || !mini->cmds->args[0])
		return (0);
	if (int_strchr(mini->cmds->args[0], '/') \
	&& check_if_file_exits(mini, mini->cmds->args[0]))
		return (0);
	fds_fill(fd, mini);
	redirect_fds(fd[2], fd[3], mini);
	if (builtin_check_and_run(mini, mini->cmds))
	{
		restore_fds(fd[0], fd[1]);
		return (0);
	}
	return (1);
}
