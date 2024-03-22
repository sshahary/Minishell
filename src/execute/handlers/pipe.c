/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/20 15:40:13 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static	char	*ft_strsep(char **stringp, char *delim)
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
		*stringp = end + strlen(delim);
	}
	else
		*stringp = NULL;
	return (start);
}

static	char *find_command_path(const char *command)
{
	char	*path;
	char	*path_copy;
	char	*dir;
	char	*command_path;
	path = getenv("PATH");
	if (path == NULL)
		ft_error("PATH envornment doesnt exist");
	path_copy = strdup(path);
	if (path_copy == NULL)
		ft_error("strdup");
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		command_path = malloc(ft_strlen(dir) + ft_strlen(command) + 2);
		if (command_path == NULL)
			ft_error("malloc");
		sprintf(command_path, "%s/%s", dir, command);
		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			return (command_path);
		}
		free(command_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

void	run_pipeline(char *commands)
{
	int		pipefd[2];
	char	*command;
	char	*end;
	pid_t	pid;
	char	*args[10];
	char	*arg;
	int		i;

	command = ft_strsep(&commands, "|");
	while ((command) != NULL)
	{
		while (*command == ' ')
			command++;
		end = command + strlen(command) - 1;
		while (end > command && *end == ' ')
			end--;
		*(end + 1) = '\0';
		if (pipe(pipefd) == -1)
			ft_error("pipe");
		pid = fork();
		if (pid == -1)
			ft_error("fork");
		if (pid == 0)
		{
			// Child process
			close(pipefd[0]); // Close read end of pipe
			dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe
			close(pipefd[1]); // Close write end of pip
			// Find full path of command
			char *full_command_path = find_command_path(command);
			if (full_command_path == NULL)
			{
				fprintf(stderr, "Command not found: %s\n", command);
				exit(EXIT_FAILURE);
				arg = strtok(full_command_path, " ");
				i = 0;
				while (arg != NULL)
				{
					args[i++] = arg;
					arg = strtok(NULL, " ");
				}
				args[i] = NULL; // Null-terminate the argument lis		
				// Executing the command
				execv(args[0], args);
				// If execv fails, print error message and exit child process
				// fprintf(stderr, "Failed to execute command: %s\n", );
				exit(EXIT_FAILURE);
			}
			else
			{
				// Parent process
				close(pipefd[1]); // Close write end of pipe
				wait(NULL); // Wait for child process to complete
				close(pipefd[0]); // Close read end of pipe
			}
		}
	}
}

int	main(void)
{
	char commands[] = "ls -l | grep test | wc -l";

	printf("Executing command: %s\n", commands);
	run_pipeline(commands);
	return (0);
}