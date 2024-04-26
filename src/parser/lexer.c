/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:33:52 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/26 09:36:23 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_lexer	*init_lexer(char *input);
static t_token	*get_token(t_lexer *lexer);

int	lexer(t_mini *mini)
{
	t_lexer	*lexer;
	t_token	*tokens;
	t_token	*temp;

	lexer = init_lexer(mini->input);
	mini->tokens = get_token(lexer);
	mini->tokens->prev = NULL;
	if (!lexer || !mini->tokens)
		return (0);
	tokens = mini->tokens;
	while (tokens->type != END)
	{
		tokens->next = get_token(lexer);
		if (!tokens->next || tokens->type == ERROR)
		{
			ft_putstr_fd("minishell: syntax error unclosed quotes\n", 2);
			mini->exit_code = 258;
			return (free(lexer), 0);
		}
		temp = tokens;
		tokens = tokens->next;
		tokens->prev = temp;
	}
	return (free(lexer), 1);
}

static t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
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
			lexer->position++;
		else if (lexer->input[lexer->position] == '|')
			return (lexer_handle_pipe(lexer));
		else if (lexer->input[lexer->position] == '<')
			return (lexer_handle_redirection_in(lexer));
		else if (lexer->input[lexer->position] == '>')
			return (lexer_handle_redirection_out(lexer));
		else if (!ft_isspace(lexer->input[lexer->position]))
		{
			return (lexer_handle_word(lexer));
		}
	}
	return (lexer_handle_eof());
}

t_token	*lexer_handle_pipe(t_lexer	*lexer)
{
	t_token	*token;

	lexer->position++;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = PIPE;
	token->value = NULL;
	return (token);
}

t_token	*lexer_handle_redirection_in(t_lexer	*lexer)
{
	t_token	*token;

	lexer->position++;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
