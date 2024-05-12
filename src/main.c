/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:40:02 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/12 17:17:10 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	g_sig = 0;

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
	signal_handler();
	configure_terminal();
	while (1)
	{
		g_sig = 0;
		mini.input = readline("➜ ");
		add_history(mini.input);
		if (!check_input(mini.input))
			break ;
		if (!parser(&mini))
		{
			free(mini.input);
			continue ;
		}
		// print_cmds(&mini);
		executor(&mini);
		free(mini.input);
		free_cmds(&mini);
	}
	clear_history();
}

static int	check_input(char *input)
{
	if (!input)
	{
		if (input)
			free (input);
		return (0);
	}
	return (1);
}