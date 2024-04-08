/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:04:00 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/09 00:35:18 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*lexer_handle_redirection_out(t_lexer	*lexer)
{
	t_token	*token;

	lexer->position++;
	lexer->position++;
	token = (t_token *)malloc(sizeof(t_token));
	if (lexer->input[lexer->position] == '>')
	{
		lexer->position++;
		token->type = REDIRECT_OUT_APPEND;
	}
	else
		token->type = REDIRECT_OUT;
	token->value = NULL;
	return (token);
}

t_token	*lexer_handle_word(t_lexer	*lexer)
{
	t_token	*token;
	int		word_length;
	int		start_position;
	int		end_position;

	start_position = lexer->position;
	while (lexer->input[lexer->position])
	{
		if (lexer->input[lexer->position] == '\'' || \
		lexer->input[lexer->position] == '\"')
			lexer_handle_quotes(lexer);
		if (ft_isspace(lexer->input[lexer->position]) && \
		!lexer->dquote && !lexer->squote)
			break ;
		lexer->position++;
	}
	if (lexer->dquote || lexer->squote)
		return (lexer_handle_error());
	end_position = lexer->position;
	word_length = end_position - start_position;
	token = (t_token *)malloc(sizeof(t_token));
	token->value = malloc((word_length + 1) * sizeof(char));
	ft_strlcpy(token->value, lexer->input + start_position, word_length + 1);
	token->type = WORD;
	return (token);
}

void	lexer_handle_quotes(t_lexer *lexer)
{
	if (lexer->input[lexer->position] == '\'' && !lexer->squote && \
	!lexer->dquote && lexer->input[lexer->position - 1] != '\\')
		lexer->squote = 1;
	else if (lexer->input[lexer->position] == '\'' && lexer->squote && \
	!lexer->dquote && lexer->input[lexer->position - 1] != '\\')
		lexer->squote = 0;
	else if (lexer->input[lexer->position] == '\"' && !lexer->squote && \
	!lexer->dquote && lexer->input[lexer->position - 1] != '\\')
		lexer->dquote = 1;
	else if (lexer->input[lexer->position] == '\"' && !lexer->squote && \
	lexer->dquote && lexer->input[lexer->position - 1] != '\\')
		lexer->dquote = 0;
}

t_token	*lexer_handle_error(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = ERROR;
	token->value = NULL;
	token->next = NULL;
	return (token);
}

t_token	*lexer_handle_eof(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = END;
	token->value = NULL;
	token->next = NULL;
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token *next;

	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		if (current->value != NULL)
			free(current->value);
		free(current);
		current = next;
	}
}
