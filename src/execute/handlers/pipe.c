/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/20 05:57:27 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	ft_pfree(void **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	strclr(char *str)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			*str = '\0';
			str++;
		}
	}
}

char	*strnew(size_t size)
{
	char	*str;
	if (size == 0)
		return (NULL);

	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*striok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*token;

	// If str is not NULL, start from str
	if (str != NULL)
		next_token = str;

	// Skip leading delimiters
	while (*next_token && ft_strchr(delim, *next_token))
		next_token++;

	// If no more tokens, return NULL
	if (*next_token == '\0')
		return NULL;

	// Find the end of the token
	token = next_token;
	while (*next_token && !ft_strchr(delim, *next_token))
		next_token++;

	// If not at the end of the string, terminate the token
	if (*next_token != '\0')
		*next_token++ = '\0';

	return (token);
}

char	*find_command_path(char *name, char **env)
{
	int		i;
	char	*str;
	char	**path;
	char	*pathstr;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!(env[i]))
		return (name);
	path = ft_split(pathstr, ':');
	i = 0;
	while (path && path[i])
	{
		str = ft_strjoin(path[i], name);
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

int	pipex(char *name, char **env, char **args, char *exe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(exe, args, env) == -1)
			ft_error("permission denied", name, 1);
		else
		{
			// Child process succeeded in executing command
		}
	}
	else if (pid < 0)
		ft_error("failed to fork", name, 1);
	else
		wait(&pid);
	return (1);
}

char	**execute(char *name, char **args, char **env)
{
	int	i;

	i = 0;
	if (!args || !*args || !**args)
		return (env);
	builtin(args);
	if (access(args[0], F_OK) != -1)
		pipex(name, env, args, args[0]);
	else
		find_command_path(name, args);
	return (env);
}

