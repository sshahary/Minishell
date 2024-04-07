/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:53:24 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/07 16:44:54 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*lexer(char *input)
{
	t_lexer	*lexer;
	t_token	*tokens;
	t_token	*temp;
	int		i;

	i = 0;
	lexer = init_lexer(input);
	tokens = get_token(lexer);
	tokens->prev = NULL;
	temp = tokens;
	while (tokens->type != END)
	{
		if (tokens->type == ERROR)
		{
			printf("minishell: syntax error unclosed quotes\n");
			free_tokens(temp);
			free(lexer);
			return (NULL);
		}
		tokens->next = get_token(lexer);
		tokens = tokens->next;
	}
	tokens = temp;
	free(lexer);
	return (tokens);
}

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	lexer->input = input;
	lexer->position = 0;
	lexer->dquote = 0;
	lexer->squote = 0;
	return (lexer);
}

t_token	*get_token(t_lexer *lexer)
{
	while (!(lexer->position >= ft_strlen(lexer->input)))
	{
		if (ft_isspace(lexer->input[lexer->position]))
		{
			lexer->position++;
		}
		if (lexer->input[lexer->position] == '|')
			return (lexer_handle_pipe(lexer));
		if (lexer->input[lexer->position] == '<')
			return (lexer_handle_redirection_in(lexer));
		if (lexer->input[lexer->position] == '>')
			return (lexer_handle_redirection_out(lexer));
		if (!ft_isspace(lexer->input[lexer->position]))
			return (lexer_handle_word(lexer));
	}
	return (lexer_handle_eof());
}

t_token	*lexer_handle_pipe(t_lexer	*lexer)
{
	t_token	*token;

	lexer->position++;
	token = (t_token *)malloc(sizeof(t_token));
	token->type = PIPE;
	token->value = NULL;
	return (token);
}

t_token	*lexer_handle_redirection_in(t_lexer	*lexer)
{
	t_token	*token;

	lexer->position++;
	token = (t_token *)malloc(sizeof(t_token));
	if (lexer->input[lexer->position] == '<')
	{
		lexer->position++;
		token->type = HEREDOC;
	}
	else
		token->type = REDIRECT_IN;
	token->value = NULL;
	return (token);
}
