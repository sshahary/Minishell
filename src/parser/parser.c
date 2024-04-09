/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:57:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/09 05:44:26 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_syntax_errors(t_mini *mini);
void	print_error_msg(t_type type);
int		check_pipe_and_redirection_errors(t_token *t);

int	parser(t_mini *mini)
{
	if (!lexer(mini))
	{
		free_tokens(mini->tokens);
		return (0);
	}
	if (!check_syntax_errors(mini))
	{
		free_tokens(mini->tokens);
		return (0);
	}
	free_tokens(mini->tokens);
	return (1);
}

int	check_syntax_errors(t_mini *mini)
{
	t_token	*tokens;

	tokens = mini->tokens;
	while (tokens)
	{
		if (!check_pipe_and_redirection_errors(tokens))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

int	check_pipe_and_redirection_errors(t_token *t)
{
	if (t->type == 1 || t->type == 2 || t->type == 3 || t->type == 4 || \
	t->type == 5)
	{
		if (t->prev == NULL || t->next->type == END)
		{
			print_error_msg(t->type);
			return (0);
		}
		else if (t->next->type != WORD || t->prev->type != WORD)
		{
			print_error_msg(t->type);
			return (0);
		}
	}
	return (1);
}

void	print_error_msg(t_type type)
{
	if (type == PIPE)
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (type == REDIRECT_IN)
		printf("minishell: syntax error near unexpected token `<'\n");
	else if (type == REDIRECT_OUT)
		printf("minishell: syntax error near unexpected token `>'\n");
	else if (type == REDIRECT_OUT_APPEND)
		printf("minishell: syntax error near unexpected token `>>'\n");
	else if (type == HEREDOC)
		printf("minishell: syntax error near unexpected token `<<'\n");
	else
		printf("minishell: syntax error\n");
}
