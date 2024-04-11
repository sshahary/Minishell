/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:35:51 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/11 13:56:56 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	t_token	*next;

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

int	tokens_size(t_token *tokens)
{
	t_token	*current;
	t_token	*next;
	int		i;

	current = tokens;
	i = 0;
	while (current != NULL)
	{
		next = current->next;
		current = next;
		i++;
	}
	return (i);
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

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*next_cmd;
	int		i;

	while (cmds != NULL)
	{
		next_cmd = cmds->next;
		free(cmds->commad);
		if (cmds->args != NULL)
		{
			i = 0;
			while (cmds->args[i] != NULL)
			{
				free(cmds->args[i]);
				i++;
			}
			free(cmds->args);
		}
		free(cmds);
		cmds = next_cmd;
	}
}
