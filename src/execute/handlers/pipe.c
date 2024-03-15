/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/15 14:33:20 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static char	*ft_strsep(char **stringp, char *delim)
{
	char	*start;
	char	*end;

	start = *stringp;
	if (*stringp == NULL)
		return (NULL);
	end = ft_strnstr(start, delim, ft_strlen(start));
	if (end != NULL)
	{
		*end = '\0';
		*stringp = end + ft_strlen(delim);
	}
	else
		*stringp = NULL;
	return (start);
}

void	run_pipeline(char *commands)
{
	int		pipefd[2];
	pid_t	pid;
	char	*command;
	int		status;
	char	*end;

	command = ft_strsep(&commands, "|");
	while ((command) != NULL)
	{
		while (*command == ' ')
			command++;
		end = command + ft_strlen(command) - 1;
		while (end > command && *end == ' ')
			end--;
		*(end + 1) = '\0';
		if (pipe(pipefd) == -1)
			ft_error("pipe");
		pid = fork();
		if ((pid) == -1)
			ft_error("fork");
		if (pid == 0)
		{
			close(pipefd[0]);
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				ft_error("dup2");
			close(pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			wait(&status);
			close(pipefd[0]);
		}
	}
}

int	main()
{
	char commands[] = "ls -l | grep test | wc -l";
	printf("Executing command: %s\n", commands);
	run_pipeline(commands);
	return (0);
}

