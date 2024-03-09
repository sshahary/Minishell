/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:55:33 by rpambhar          #+#    #+#             */
/*   Updated: 2024/03/09 03:20:16 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*parser(t_token **tokens)
{
	int index = 0;

	return (parse_pipe(tokens, &index));
}

t_ast_node	*parse_pipe(t_token **tokens, int *index)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_commands(tokens, index);
	if (tokens[*index] != NULL && tokens[*index]->type == T_PIPE)
	{
		(*index)++;
		t_ast_node *right = parse_pipe(tokens, index);
		return (create_new_node(N_PIPE, NULL, left, right));
	}
	else
	{
		(void)right;
		return (left);
	}
}

t_ast_node	*parse_commands(t_token **tokens, int *index)
{
	char	**args;
	int		args_count;
	int		i;

	args_count = 0;
	i = *index;
	while (tokens[*index] != NULL && tokens[*index]->type != T_PIPE)
	{
		args_count++;
		(*index)++;
	}
	args = malloc((args_count + 1) * sizeof(char *));
	args[args_count] = NULL;
	*index = i;
	i = 0;
	while (i < args_count)
	{
		args[i] = ft_strdup(tokens[*index]->value);
		(*index)++;
		i++;
	}
	return (create_new_node(N_COMMAND, args, NULL, NULL));
}

t_ast_node	*create_new_node(t_node_type t, char **a, t_ast_node *p, t_ast_node *n)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = t;
	node->args = a;
	node->prev = p;
	node->next = n;
	return (node);
}