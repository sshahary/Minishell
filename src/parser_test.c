/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:40:02 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/12 10:54:42 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

static int	check_input(char *input);

int	main(void)
{
	t_mini	mini;
	// atexit(check_leaks);

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
		print_cmds(&mini);
		free(mini.input);
		free_cmds(&mini);
	}
	clear_history();
}

static int	check_input(char *input)
{
	if (ft_strncmp("exit", input, 4) == 0)
	{
		free(input);
		exit(EXIT_SUCCESS);
	}
	if (!input || input[0] == '\0')
	{
		if (input)
			free (input);
		return (0);
	}
	return (1);
}