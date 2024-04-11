/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:04:00 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/11 13:43:48 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*lexer_handle_redirection_out(t_lexer	*lexer)
{
	t_token	*token;

	lexer->position++;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (lexer->input[lexer->position++] == '>')
	{
		lexer->position++;
		token->type = REDIRECT_OUT_APPEND;
	}
	else
		token->type = REDIRECT_OUT;
	token->value = NULL;
	return (token);
}

t_token	*lexer_handle_word(t_lexer	*l)
{
	int		sp;
	int		quotes;

	quotes = 0;
	sp = l->position;
	while (l->input[l->position])
	{
		if (l->input[l->position] == '\'' || l->input[l->position] == '\"')
			lexer_handle_quotes(l, &quotes);
		if (ft_isspace(l->input[l->position]) && !l->dquote && !l->squote)
			break ;
		if (l->input[l->position] == '|' || l->input[l->position] == '<' || \
		l->input[l->position] == '>')
			break ;
		l->position++;
	}
	if (l->dquote || l->squote)
		return (lexer_handle_error());
	return (get_word(sp, l->position, quotes, l));
}

t_token	*get_word(int sp, int ep, int quotes, t_lexer *l)
{
	int		word_length;
	t_token	*token;

	if (quotes)
	{
		sp++;
		ep--;
	}
	word_length = ep - sp;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = malloc((word_length + 1) * sizeof(char));
	ft_strlcpy(token->value, l->input + sp, word_length + 1);
	token->type = WORD;
	return (token);
}

void	lexer_handle_quotes(t_lexer *lexer, int *quotes)
{
	if (lexer->input[lexer->position] == '\'' && !lexer->squote && \
	!lexer->dquote && lexer->input[lexer->position - 1] != '\\')
	{
		lexer->squote = 1;
		*quotes = 1;
	}
	else if (lexer->input[lexer->position] == '\'' && lexer->squote && \
	!lexer->dquote && lexer->input[lexer->position - 1] != '\\')
		lexer->squote = 0;
	else if (lexer->input[lexer->position] == '\"' && !lexer->squote && \
	!lexer->dquote && lexer->input[lexer->position - 1] != '\\')
	{
		lexer->dquote = 1;
		*quotes = 1;
	}
	else if (lexer->input[lexer->position] == '\"' && !lexer->squote && \
	lexer->dquote && lexer->input[lexer->position - 1] != '\\')
		lexer->dquote = 0;
}

t_token	*lexer_handle_error(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = ERROR;
	token->value = NULL;
	token->next = NULL;
	return (token);
}
