/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/18 16:45:12 by sshahary         ###   ########.fr       */
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
		ft_error("strdup", 1);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		command_path = malloc(ft_strlen(dir) + ft_strlen(command) + 2);
		if (command_path == NULL)
			return (1);
		sprintf(command_path, "%s/%s", dir, command);
		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			return (command_path);
		}
		free(command_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

