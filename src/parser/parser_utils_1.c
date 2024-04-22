/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:35:51 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/22 09:46:52 by rpambhar         ###   ########.fr       */
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
		ft_putstr_fd("minishell: syntax error\n", 2);
}

void	free_cmds(t_mini *mini)
{
	int		i;
	t_cmds	*temp;

	while (mini->cmds)
	{
		i = 0;
		free(mini->cmds->commad);
		while (mini->cmds->args && mini->cmds->args[i])
		{
			free(mini->cmds->args[i]);
			i++;
		}
		if (mini->cmds->args)
			free(mini->cmds->args);
		temp = mini->cmds->next;
		free(mini->cmds);
		mini->cmds = temp;
	}
}
