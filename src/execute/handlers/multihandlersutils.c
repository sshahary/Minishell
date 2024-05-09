/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multihandlersutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:28 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/09 22:29:15 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

void	close_fds(int **fds, int n_cmds)
{
	int	i;

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
	int	i;
	int	status;

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
