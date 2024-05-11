/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:35:51 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/11 15:20:22 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_pipe_and_redirection_errors(t_token *t);
static void	print_error_msg(t_type type);

t_token	*lexer_handle_eof(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = END;
	token->value = NULL;
	token->next = NULL;
	return (token);
}

int	check_syntax_errors(t_mini *mini)
{
	t_token	*tokens;

	tokens = mini->tokens;
	while (tokens)
	{
		if (!check_pipe_and_redirection_errors(tokens))
		{
			mini->exit_code = 258;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

static int	check_pipe_and_redirection_errors(t_token *t)
{
	if (t->type == 1)
	{
		if (t->prev == NULL || (t->next && t->next->type == END))
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
	else if (t->type == 2 || t->type == 3 || t->type == 4 || t->type == 5)
	{
		if (t->next->type != WORD)
		{
			print_error_msg(END);
			return (0);
		}
	}
	return (1);
}

static void	print_error_msg(t_type type)
{
	if (type == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (type == REDIRECT_IN)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (type == REDIRECT_OUT)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (type == REDIRECT_OUT_APPEND)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (type == HEREDOC)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n"\
		, 2);
}
