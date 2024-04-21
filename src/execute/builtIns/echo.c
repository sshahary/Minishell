
 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:55 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/22 11:35:22 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	int		args_count(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void	echo(char **argv)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	if (args_count(argv) > 1)
	{
	 	while (argv[i] && ft_strncmp(argv[1], "-n", 2) == 0)
		{
			newline = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (newline == 0)
		printf("\n");
}
