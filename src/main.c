/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:34:12 by rpambhar          #+#    #+#             */
/*   Updated: 2024/03/09 03:32:44 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_token		**tokens;
	t_ast_node	*ast;

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
	//free_tokens(tokens);
	return (EXIT_SUCCESS);
}
