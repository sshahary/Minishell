/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:57:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/09 16:36:53 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (!get_cmds(mini))
	{
		free_tokens(mini->tokens);
		return (0);
	}
	if (!expander(mini))
	{
		free_tokens(mini->tokens);
		return (0);
	}
	handle_redirection(mini);
	clean_cmds(mini);
	free_tokens(mini->tokens);
	return (1);
}

int	get_cmds(t_mini *mini)
{
	t_token	*tokens;
	t_cmds	*cmds;

	tokens = mini->tokens;
	cmds = NULL;
	if (!create_cmds(tokens, &cmds))
		return (0);
	if (cmds == NULL)
		return (1);
	mini->cmds = cmds;
	return (1);
}

int	create_cmds(t_token *tokens, t_cmds **cmds)
{
	t_cmds	*prev_cmd;

	prev_cmd = NULL;
	while (tokens->type != END)
	{
		if (tokens->prev == NULL || tokens->prev->type == PIPE)
		{
			if (!create_new_cmd(&prev_cmd, &tokens, cmds))
				return (0);
		}
		if (tokens->type != PIPE)
		{
			if (!get_args(&tokens, prev_cmd))
				return (0);
		}
		else if (tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (1);
}

int	create_new_cmd(t_cmds **prev_cmd, t_token **tokens, t_cmds **cmds)
{
	t_cmds	*new_cmd;

	new_cmd = NULL;
	new_cmd = malloc(sizeof(t_cmds));
	if (new_cmd == NULL)
		return (0);
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->prev = (*prev_cmd);
	if ((*prev_cmd) != NULL)
		(*prev_cmd)->next = new_cmd;
	if ((*cmds) == NULL)
		(*cmds) = new_cmd;
	(*prev_cmd) = new_cmd;
	if ((*tokens)->prev != NULL && (*tokens)->prev->type != PIPE)
		(*tokens) = (*tokens)->next;
	return (1);
}

int	get_args(t_token **tokens, t_cmds *cmd)
{
	int		arg_count;
	t_token	*temp;

	arg_count = 0;
	temp = (*tokens);
	while (temp->type != PIPE && temp->type != END)
	{
		arg_count++;
		temp = temp->next;
	}
	if (arg_count == 0)
		return (1);
	cmd->args = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd->args)
		return (0);
	cmd->args[arg_count] = NULL;
	if (!fill_args_array(arg_count, &cmd, tokens))
		return (0);
	return (1);
}
