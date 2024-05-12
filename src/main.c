/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:40:02 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/13 01:34:04 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig = 0;

static int	check_input(char *input);
static void	prompt(t_mini *mini);

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	mini.env = env;
	rl_bind_key('\t', rl_complete);
	using_history();
	signal_handler();
	prompt(&mini);
	clear_history();
}

static int	check_input(char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	return (1);
}

static void	prompt(t_mini *mini)
{
	while (1)
	{
		g_sig = 0;
		mini->input = readline("➜ ");
		if (!mini->input)
			break ;
		if (!check_input(mini->input))
			continue ;
		add_history(mini->input);
		if (!parser(mini))
		{
			free(mini->input);
			continue ;
		}
		executor(mini);
		free(mini->input);
		free_cmds(mini);
	}
}
