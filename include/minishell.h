/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:33:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/03/09 03:20:40 by rpambhar         ###   ########.fr       */
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

typedef enum s_token_type
{
	T_COMMAND,
	T_ARGUMENT,
	T_PIPE,
	T_REDIRECT,
	T_END
}	t_token_type;

typedef enum s_node_type
{
	N_COMMAND,
	N_ARGUMENT,
	N_PIPE,
	N_REDIRECT_IN,
	N_REDIRECT_OUT,
	N_REDIRECT_OUT_APPEND,
	N_HEREDOC
}	t_node_type;

typedef struct s_token
{
	t_token_type	type;
	char		*value;
}	t_token;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	struct s_ast_node	*prev;
	struct s_ast_node	*next;
}	t_ast_node;

// Lexer
t_token		**lexer(const char *input);
t_token		*create_new_token(t_token_type type, char *value);
void		free_tokens(t_token **tokens);
void		assign_tokens(t_token **tokens, char **split_tokens, int token_count);

// Parser
t_ast_node	*parser(t_token **tokens);
t_ast_node	*parse_pipe(t_token **tokens, int *index);
t_ast_node	*parse_commands(t_token **tokens, int *index);
t_ast_node	*create_new_node(t_node_type t, char **a, t_ast_node *p, t_ast_node *n);

// Tests
void		print_tokens(t_token **tokens);
void		print_ast(t_ast_node *node, int level);

#endif