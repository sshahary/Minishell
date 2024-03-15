/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtlns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:33 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/15 16:45:40 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	echo(int argc, char *argv[]);

int	main()
{
	char	input[1024];
	char	*tokens[100];
	char	*token;
	int		argc;

	printf("Minishell >> ");
	while (fgets(input, sizeof(input), stdin) != NULL)
	{
		argc = 0;
		token = strtok(input, " \n");
		while (token != NULL)
		{
			tokens[argc++] = token;
			token = strtok(NULL, " \n");
		}
		tokens[argc] = NULL;
		if (ft_strncmp(tokens[0], "echo", 4) == 0)
			echo(argc, tokens);
		else
			printf("Command not found: %s\n", tokens[0]);
		printf("Minishell>> ");
	}
	return (0);
}
