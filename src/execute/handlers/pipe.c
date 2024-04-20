/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/20 14:57:43 by sshahary         ###   ########.fr       */
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

int	pipex(t_mini *mini, char *exe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		printf("exe = %s\n", exe);
		printf("cmds->comand %s\n", mini->cmds->commad);
		printf("");
		if (execve(exe, mini->cmds->args, mini->env) == -1)
			ft_error("permission denied", mini->cmds->commad, 1);
	}
	else if (pid < 0)
		ft_error("failed to fork", mini->cmds->commad, 1);
	else
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status)) // checks if the 	CHILD process terminated normally
			mini->exit_code = WEXITSTATUS(status);

	return (mini->exit_code);
}
