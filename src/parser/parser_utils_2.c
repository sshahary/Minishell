/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:35:55 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/11 10:43:22 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_args_array(int arg_count, t_cmds **cmd, t_token **tokens)
{
	int	index;

	index = 0;
	while (index < arg_count)
	{
		if ((*tokens)->type == WORD)
			(*cmd)->args[index] = ft_strdup((*tokens)->value);
		else
			(*cmd)->args[index] = redirection_to_string((*tokens));
		(*tokens) = (*tokens)->next;
		index++;
	}
}

char	*redirection_to_string(t_token *tokens)
{
	char	*output;

	output = (char *)ft_calloc(3, sizeof(char));
	if (tokens->type == REDIRECT_IN)
		output[0] = '<';
	else if (tokens->type == REDIRECT_OUT)
		output[0] = '>';
	if (tokens->type == REDIRECT_OUT_APPEND)
	{
		output[0] = '>';
		output[1] = '>';
	}
	else if (tokens->type == HEREDOC)
	{
		output[0] = '<';
		output[1] = '<';
	}
	return (output);
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
	return (1);
}

void	reverse_cmds(t_cmds **head)
{
	t_cmds	*prev_node;
	t_cmds	*current_node;
	t_cmds	*next_node;

	prev_node = NULL;
	current_node = *head;
	next_node = NULL;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		current_node->next = prev_node;
		current_node->prev = next_node;
		prev_node = current_node;
		current_node = next_node;
	}
	*head = prev_node;
}
