/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:34:12 by rpambhar          #+#    #+#             */
/*   Updated: 2024/03/09 10:37:48 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_leaks(void);

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_token		**tokens;
	t_ast_node	*ast;

	atexit(check_leaks);
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = readline("minishell> ");
		tokens = lexer(input);
		//print_tokens(tokens);
		ast = parser(tokens);
		print_ast(ast, 0);
		break ;
	}
	free_tokens(tokens);
	free_ast(ast);
	free(input);
	return (EXIT_SUCCESS);
}


void	check_leaks(void)
{
	system("leaks minishell");
}