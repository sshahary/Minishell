/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:40:02 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/03 18:32:27 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

// void	check_leaks(void)
// {
// 	system("leaks minishell");
// }

static int	check_input(char *input);

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	(void)argc;
	(void)argv;
	// atexit(check_leaks);

	mini.env = env;
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		mini.input = readline("➜ ");
		add_history(mini.input);
		if (!check_input(mini.input))
			continue ;
		if (!parser(&mini))
		{
			free(mini.input);
			continue ;
		}
		// print_cmds(&mini);
		// execute(&mini);
		executor(&mini);
		free(mini.input);
		free_cmds(&mini);
	}
	clear_history();
}

static int	check_input(char *input)
{
	// if (ft_strcmp("exit", input) == 0)
	// {
	// 	free(input);
	// 	exit(EXIT_SUCCESS);
	// }
	if (ft_strcmp("clear", input) == 0)
	{
		free(input);
		printf("\033[H\033[J");
		return (0);
	}
	if (!input || input[0] == '\0')
	{
		if (input)
			free (input);
		return (0);
	}
	return (1);
}