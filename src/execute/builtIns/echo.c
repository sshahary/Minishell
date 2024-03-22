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

void	echo(int argc, char *argv[])
{
	int	i;
	int	newline;

	newline = 1;
	if (argc > 1 && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		newline = 0;
		argc--;
		argv++;
	}
	i = 1;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

// int	main(int ac, char *argv[])
// {
// 	if (ac < 2)
// 		return (1);
// 	echo(ac, argv);
// 	return (0);
// }
