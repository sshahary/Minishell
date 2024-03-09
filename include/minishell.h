/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:33:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/03/09 01:13:31 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

typedef enum
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT,
	END
}	token_type;

typedef struct s_token
{
	token_type	type;
	char		*value;
}	t_token;

// Lexer
t_token	**lexer(const char *input);
t_token	*create_new_token(token_type type, char *value);
void	free_token(t_token *token);
void	assign_tokens(t_token **tokens, char **split_tokens, int token_count);

// Tests
void	print_tokens(t_token **tokens);

#endif