/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/14 17:56:39 by sshahary         ###   ########.fr       */
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

	command = ft_strsep(&commands, "|");
	// Split commands based on the pipe character '|'
	while ((command) != NULL)
	{
		// Trim leading and trailing spaces
		while (*command == ' ')
			command++;
		char *end = command + ft_strlen(command) - 1;
		while (end > command && *end == ' ')
			end--;
		*(end + 1) = '\0';	
		// Create pipe
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		// Fork a child process
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{	// Child process
			// Close read end of the pipe
			close(pipefd[0]);	
			// Redirect stdout to the write end of the pipe
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			// Close unnecessary file descriptors
			close(pipefd[1]);	
			// Execute the command
			if (execlp(command, command, NULL) == -1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{	// Parent process
			// Close write end of the pipe
			close(pipefd[1]);
			// Wait for child process to complete
			wait(&status);
			// Close read end of the pipe
			close(pipefd[0]);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		return (-1);
	}
	// Skip the program name (argv[0]) and pass the remaining arguments to run_pipeline
	run_pipeline(*argv + 1);
	return (0);
}