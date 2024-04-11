/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:57:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/09 12:48:11 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_syntax_errors(t_mini *mini);
void	print_error_msg(t_type type);
int		check_pipe_and_redirection_errors(t_token *t);
int		get_cmds(t_mini *mini);
char	*redirection_to_string(t_token *tokens);
int		get_args(t_mini *mini, t_token *tokens);
void	free_cmds(t_cmds *cmds);
void	reverse_cmds(t_cmds **head);

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
	get_cmds(mini);
	free_cmds(mini->cmds);
	free_tokens(mini->tokens);
	return (1);
}

int	get_cmds(t_mini *mini)
{
	t_token	*tokens;
	t_cmds	*cmds;

	tokens = mini->tokens;
	while (tokens->type != END)
	{
		if (tokens->prev == NULL)
		{
			mini->cmds = malloc(sizeof(t_cmds));
			mini->cmds->prev = NULL;
			cmds = mini->cmds;
		}
		if (tokens->type != PIPE)
		{
			if (tokens->prev == NULL || tokens->prev->type == PIPE)
			{
				mini->cmds->commad = ft_strdup(tokens->value);
				tokens = tokens->next;
			}
		}
		if (tokens->type != PIPE)
			get_args(mini, tokens);
		if (tokens->type == PIPE && tokens->next->type != END)
		{
			mini->cmds->next = malloc(sizeof(t_cmds));
			mini->cmds->next->prev = mini->cmds;
			mini->cmds = mini->cmds->next;
		}
		else
			mini->cmds->next = NULL;
		if (tokens->next)
			tokens = tokens->next;
	}
	mini->cmds = cmds;
	
	return (1);
}

int	get_args(t_mini *mini, t_token *tokens)
{
	int		i;
	int		j;
	t_token	*temp;

	i = 0;
	temp = tokens;
	while (temp->type != PIPE && temp->type != END)
	{
		i++;
		temp = temp->next;
	}
	mini->cmds->args = malloc((i + 1) * sizeof(char *));
	mini->cmds->args[i] = NULL;
	j = 0;
	printf("J: %d\n", i);
	while (i > 0 && j < i)
	{

		if (tokens->type == WORD)
			mini->cmds->args[j] = ft_strdup(tokens->value);
		if (tokens->type != WORD)
			mini->cmds->args[j] = redirection_to_string(tokens);
		if (tokens->next)
			tokens = tokens->next;
		j++;
	}
	return (0);
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
	if (t->type == 0)
		printf("WORD: %s\n", t->value);
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

	while (cmds != NULL) {
		next_cmd = cmds->next;
		free(cmds->commad);
		if (cmds->args != NULL)
		{

			i = 0;
			while (cmds->args[i] != NULL)
			{
				printf("ARGS: %s\n", cmds->args[i]);
				free(cmds->args[i]);
				i++;
			}
			free(cmds->args);
		}
		free(cmds);
		cmds = next_cmd;
	}
}

void	reverse_cmds(t_cmds **head)
{
	t_cmds	*prev_node;
	t_cmds	*current_node;
	t_cmds	*next_node;

	prev_node = NULL;
	current_node = *head;
	next_node = NULL;
	while (current_node != NULL) {
		next_node = current_node->next;
		current_node->next = prev_node;
		current_node->prev = next_node;
		prev_node = current_node;
		current_node = next_node;
	}
	*head = prev_node;
}