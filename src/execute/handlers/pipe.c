/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/22 04:37:45 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char	*find_command_path(char *name, char **env)
{
	int		i;
	char	*str;
	char	**path;
	char	*pathstr;

	i = 0;
	while (env[i] && ft_strcmp(env[i], "PATH="))
		i++;
	if (!(env[i]))
		return (name);
	path = ft_split(pathstr, ':');
	i = 0;
	while (path && path[i])
	{
		str = strjoinslash(path[i], name);
		if (!(access(str, F_OK)))
		{
			ft_pfree((void **)path);
			return (str);
		}
		free(str);
		i++;
	}
	ft_pfree((void **)path);
	return (name);
}

int			pipex(t_mini *mini)
{
	pid_t	pid;
	int		res;
	int		status;
	char	*path;

	res = EXIT_SUCCESS;
	path = find_command_path(mini->cmds->commands[0], mini->env);
	mini->cmds->next = mini->list->content;
	if (mini->flag == 1)
	{
		mini->cmds->next = mini->list->next->content;
		mini->preflag = 1;
		pipe(mini->fds);
	}
	pid = fork();
	if (pid == 0)
		child_process(mini);
	waitpid(pid, &status, 0);
	if (mini->flag == 1)
		close(mini->fds[1]);
	if (mini->fds[0] != 0)
		close(mini->fds[0]);
	return (res);
}

int main(void) {
    // Create a mock t_mini structure
    t_mini mini;
    // Initialize mini.cmds, mini.list, mini.env (consider using mock data)
    mini.flag = 0; // Test without pipe initially

    // Test case 1: Simple execution (no pipe)
    printf("Test 1: Simple execution\n");
    pipex(&mini);

    // Test case 2: Execution with pipe (modify mini.flag and list accordingly)
    printf("Test 2: Execution with pipe\n");
    mini.flag = 1;
    // Update mini.list to simulate piped commands
    pipex(&mini);

    return (0);
}