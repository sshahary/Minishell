/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:40:02 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/11 10:31:49 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

static int	prompt(char **input);

int	main(void)
{
	t_mini	mini;

	atexit(check_leaks);
	while (1)
	{
		if (!prompt(&mini.input))
			break;
		if (!parser(&mini))
		{
			free(mini.input);
			continue ;
		}
		free(mini.input);
		free_cmds(mini.cmds);
	}
}

static int	prompt(char **input)
{
	*input = readline("➜ ");
	if (ft_strncmp("exit", *input, 4) == 0)
	{
		free (*input);
		return (0);
	}
	return (1);
}