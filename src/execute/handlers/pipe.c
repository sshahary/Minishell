/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:44 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/19 15:15:00 by sshahary         ###   ########.fr       */
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

char *find_command_path(char *cmd, char **env)
{
	
	int	i;

	i = 0;
	if (ft_strlen(cmd) == 1 && cmd[0] == '~')
		cmd = "$HOME";
	else if (cmd[0] == '$')
		cmd += 1;

	while (env[i])
	{
		if (!(ft_strncmp(cmd, env[i], ft_strlen(cmd))))
		{
			if (env[i][ft_strlen(cmd)] == '=')
				return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	return ("");
}


// int main(int argc, char **argv, char **env) {
//     if (argc != 2) {
//         printf("Usage: %s <command>\n", argv[0]);
//         return 1;
//     }

//     char *cmd = argv[1];

//     // Print out the contents of the environment array
//     printf("Environment variables:\n");
//     for (int i = 0; env[i] != NULL; i++) {
//         printf("%s\n", env[i]);
//     }

//     char *path = find_command_path(cmd, env);
    
//     if (*path) {
//         printf("Path for %s: %s\n", cmd, path);
//     } else {
//         printf("Path for %s not found\n", cmd);
//     }

//     return 0;
// }