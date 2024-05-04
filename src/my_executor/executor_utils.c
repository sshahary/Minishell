/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:20:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/04 14:31:54 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
    int i;

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
