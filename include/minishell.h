/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:33:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/07 13:17:55 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

typedef enum s_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_OUT_APPEND,
	HEREDOC,
	ERROR,
	END,
}	t_type;

typedef struct s_token
{
	t_type		type;
	char		*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_parser
{
	t_token		*tokens;
	int			exit_code;
}	t_parser;

typedef struct s_lexer
{
	char	*input;
	int		position;
	int		dquote;
	int		squote;
}	t_lexer;

// Lexer
t_token	*lexer(char *input);
t_lexer	*init_lexer(char *input);
t_token	*get_token(t_lexer *lexer);
t_token	*lexer_handle_pipe(t_lexer	*lexer);
t_token	*lexer_handle_redirection_in(t_lexer	*lexer);
t_token	*lexer_handle_redirection_out(t_lexer	*lexer);
t_token	*lexer_handle_word(t_lexer	*lexer);
t_token	*lexer_handle_error();
t_token	*lexer_handle_eof();
void	lexer_handle_quotes(t_lexer *lexer);
void	free_tokens(t_token *tokens);



//execution
#define MAX_COMMAND_LENGTH 100

typedef struct s_command
{
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_COMMAND_LENGTH]; // You can adjust the size as needed
    int num_arguments;
    char *environment_variables[100]; // Example for environment variables
    int num_environment_variables;
}	t_command;
int			ft_error(char *str);
void		run_pipeline(char *commands);


#endif