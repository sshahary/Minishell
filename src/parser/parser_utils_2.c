/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:35:55 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/11 15:35:12 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*redirection_to_string(t_token *tokens);

int	fill_args_array(int arg_count, t_cmds **cmd, t_token **tokens)
{
	int	index;

	index = 0;
	while (index < arg_count)
	{
		if ((*tokens)->type == WORD)
		{
			(*cmd)->args[index] = ft_strdup((*tokens)->value);
			if ((*cmd)->args[index] == NULL)
				return (0);
		}
		else
		{
			(*cmd)->args[index] = redirection_to_string((*tokens));
			if ((*cmd)->args[index] == NULL)
				return (0);
		}
		(*tokens) = (*tokens)->next;
		index++;
	}
	return (1);
}

static char	*redirection_to_string(t_token *tokens)
{
	char	*output;

	output = (char *)ft_calloc(3, sizeof(char));
	if (!output)
		return (NULL);
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

void	free_cmds(t_mini *mini)
{
	int		i;
	t_cmds	*temp;

	while (mini->cmds)
	{
		i = 0;
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

void	clean_cmds(t_mini *mini)
{
	while (mini->cmds)
	{
		if (!mini->cmds->args[0])
			remove_cmd_node(mini, mini->cmds);
		else
		{
			if (mini->cmds->next)
				mini->cmds = mini->cmds->next;
			else
				break ;
		}
	}
	if (mini->cmds)
	{
		while (mini->cmds->prev)
			mini->cmds = mini->cmds->prev;
	}
}
