
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

void	echo(t_cmds *cmds, t_mini mini)
{
	int	i;
	int	newline;
	(void)mini;
	newline = 0;
	i = 1;
	if (args_count(cmds->args) > 1)
	{
	 	while (cmds->args[i] && ft_strncmp(cmds->args[i], "-n", 2) == 0)
		{
			newline = 1;
			i++;
		}
		while (cmds->args[i])
		{
			ft_putstr_fd(cmds->args[i], cmds->fd_out);
			if (cmds->args[i + 1] && cmds->args[i][0] != '\0')
				write(cmds->fd_out, " ", 1);
			i++;
		}
	}
	if (newline == 0)
		ft_putchar_fd('\n', cmds->fd_out);
}

// int	main(void)
// {
//     t_mini mini;  // Create a dummy t_mini structure (fill with test data if needed)

//     // Allocate memory for mini.cmds
//     mini.cmds = malloc(sizeof(t_cmds));
//     if (mini.cmds == NULL) {
//         // Handle allocation failure
//         return 1;
//     }

//     // Test case 1: Simple string printing
//     mini.cmds->args = malloc(3 * sizeof(char*)); // Allocate memory for 3 strings
//     mini.cmds->args[0] = strdup("echo"); // Command name
//     mini.cmds->args[1] = strdup("$?"); // First argument
//     mini.cmds->args[2] = strdup(""); // Second argument
//     mini.cmds->args[3] = NULL; // NULL terminator
//     echo(&mini);

//     // Free memory
//     for (int i = 0; mini.cmds->args[i] != NULL; i++) {
//         free(mini.cmds->args[i]);
//     }
//     free(mini.cmds->args);
//     free(mini.cmds);

//     return 0;
// }
