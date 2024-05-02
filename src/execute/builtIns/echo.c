
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


// static void		exit_code(t_mini *mini)
// {
// 	ft_putstr_fd(ft_itoa(mini->exit_code), 1);
// }

// static void		echoenv(t_mini *mini, int i)
// {
// 	char	*value;
// 	if (mini->cmds->args[1][0] == '$' && mini->cmds->args[1][1] == '?')
// 		exit_code(mini);
// 	value = find_command_path(&(mini->cmds->args[i][1]), mini->env);
// 	ft_putstr_fd(value, mini->cmds->fd_in);
// }

// static	int		args_n(char *cmds)
// {
// 	int	i;

// 	if (ft_strncmp(cmds, "-n", 2) != 0)
// 		return (0);
// 	i = 2;
// 	while (cmds[i])
// 	{
// 		if (cmds[i] != 'n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void	echo(t_mini *mini)
// {
// 	int	i;
// 	int	res;

// 	i = 1;
// 	res = 0;
// 	while (args_n(mini->cmds->args[i]))
// 	{
// 		res = -1;
// 		i++;
// 	}
// 	while (mini->cmds->args[i])
// 	{
// 		if (mini->cmds->args[i][0] == '\'')
// 			res = remove_char(mini->cmds->args[i], '\'');
// 		if (mini->cmds->args[i][0] == '$' && res != 1)
// 			echoenv(mini, i);
// 		else
// 			ft_putstr_fd(mini->cmds->args[i], mini->cmds->fd_out);
// 			if (mini->cmds->args[i + 1] != NULL)
// 			ft_putchar_fd(' ', mini->cmds->fd_out);
// 		i++;
// 	}
// 	if (res != -1)
// 		ft_putchar_fd('\n', mini->cmds->fd_out);
// }


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
