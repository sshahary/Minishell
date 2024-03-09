/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:33:30 by rpambhar          #+#    #+#             */
/*   Updated: 2024/03/09 01:50:46 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Splits the input into tokens
 *
 * @param input
 * @return t_token**
 */
t_token	**lexer(const char *input)
{
	t_token	**tokens;
	char	**split_tokens;
	int		token_count;
	int		i;

	i = -1;
	token_count = 0;
	split_tokens = ft_split(input, ' ');
	while (split_tokens[token_count])
		token_count++;
	tokens = (t_token **)malloc(sizeof(t_token *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	assign_tokens(tokens, split_tokens, token_count);
	while (split_tokens[++i])
		free(split_tokens[i]);
	free(split_tokens);
	return (tokens);
}

/**
 * @brief Create a new token object
 *
 * @param type
 * @param value
 * @return t_token*
 */
t_token	*create_new_token(token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	return (token);
}

/**
 * @brief frees the array of tokens
 *
 * @param token
 */
void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}

/**
 * @brief Parses the input and creates new tokens
 *
 * @param tokens
 * @param split_tokens
 * @param token_count
 */
void	assign_tokens(t_token **tokens, char **split_tokens, int token_count)
{
	int			i;
	token_type	type;

	i = 0;
	while (i < token_count)
	{
		if (i == 0)
			type = T_COMMAND;
		else if (strcmp(split_tokens[i], "|") == 0)
			type = T_PIPE;
		else if (strcmp(split_tokens[i], ">") == 0)
			type = T_REDIRECT;
		else
			type = T_ARGUMENT;
		tokens[i] = create_new_token(type, split_tokens[i]);
		i++;
	}
	tokens[token_count] = NULL;
}
