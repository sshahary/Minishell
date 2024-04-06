/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:55:33 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/04 18:18:37 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*parser(t_token **tokens)
{
	int index = 0;

	return (parse_pipes_and_redirections(tokens, &index));
}

t_ast_node	*parse_pipes_and_redirections(t_token **tokens, int *index)
{
	t_ast_node	*prev;
	t_ast_node	*next;
	t_type		temp;

	prev = parse_commands(tokens, index);
	if (tokens[*index] != NULL && tokens[*index]->type != COMMAND && tokens[*index]->type != ARGUMENT)
	{
		temp = tokens[*index]->type;
		(*index)++;
		next = parse_pipes_and_redirections(tokens, index);
		return (create_new_node(temp, NULL, prev, next));
	}
	else
	{
		(void)next;
		return (prev);
	}
}

t_ast_node	*parse_commands(t_token **tokens, int *index)
{
	char	**args;
	int		args_count;
	int		i;

	args_count = 0;
	i = *index;
	while (tokens[*index] != NULL && (tokens[*index]->type == COMMAND || tokens[*index]->type == ARGUMENT))
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
	return (create_new_node(COMMAND, args, NULL, NULL));
}

t_ast_node	*create_new_node(t_type t, char **a, t_ast_node *p, t_ast_node *n)
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

void	free_ast(t_ast_node *node)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	free_ast(node->next);
	free_ast(node->prev);
	if (node->args != NULL)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	free(node);
}