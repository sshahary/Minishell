/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:34:12 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/07 16:44:19 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_leaks(void);
void print_tokens(t_token *tokens);

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_parser	parser;


	atexit(check_leaks);
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = readline("➜ ");
		if (ft_strncmp("exit", input, 4) == 0)
		{
			free(input);
			break ;
		}
		parser.tokens = lexer(input);
		if (parser.tokens == NULL)
		{
			free(input);
			free_tokens(parser.tokens);
			continue;
		}
		free(input);
		free_tokens(parser.tokens);
	}
	// print_tokens(parser.tokens);
	return (EXIT_SUCCESS);
}

void print_tokens(t_token *tokens)
{
	while (tokens->next)
	{
		if (tokens->type == PIPE)
			printf("PIPE\n");
		if (tokens->type == WORD)
			printf("WORD\n");
		tokens = tokens->next;
	}
}

void	check_leaks(void)
{
	system("leaks minishell");
}