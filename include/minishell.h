/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:33:54 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/20 16:35:42 by rpambhar         ###   ########.fr       */
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

typedef struct s_cmds
{
	char		*commad;
	char		**args;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_mini
{
	char		*input;
	char		**env;
	t_token		*tokens;
	t_cmds		*cmds;
	int			exit_code;
}	t_mini;

typedef struct s_lexer
{
	char	*input;
	int		position;
	int		dquote;
	int		squote;
}	t_lexer;

typedef struct s_expander
{
	char	*input;
	int		i;
}	t_expander;

// Lexer
int		lexer(t_mini *mini);
t_token	*lexer_handle_pipe(t_lexer	*lexer);
t_token	*lexer_handle_redirection_in(t_lexer	*lexer);
t_token	*lexer_handle_redirection_out(t_lexer	*lexer);
t_token	*lexer_handle_word(t_lexer	*lexer);
t_token	*get_word(int sp, int ep, int quotes, t_lexer *l);
t_token	*lexer_handle_error();
t_token	*lexer_handle_eof();
void	lexer_handle_quotes(t_lexer *lexer, int *quotes);
void	free_tokens(t_token *tokens);

// Parser
int		parser(t_mini *mini);
int		check_syntax_errors(t_mini *mini);
int		check_pipe_and_redirection_errors(t_token *t);
int		get_cmds(t_mini *mini);
int		create_cmds(t_token *tokens, t_cmds **cmds);
int		create_new_cmd(t_cmds **prev_cmd, t_token **tokens, t_cmds **cmds);
int		get_args(t_token **tokens, t_cmds *cmd);
int		fill_args_array(int arg_count, t_cmds **cmd, t_token **tokens);
void	reverse_cmds(t_cmds **head);
void	free_cmds(t_mini *mini);
void	print_error_msg(t_type type);
char	*redirection_to_string(t_token *tokens);

// // Expander
// int		expander(t_mini *mini);
// int		check_and_expand(char **str_ptr);
// char	*get_env(const char *name, char **env);
// char	*join_strings(char **array);
// void	*ft_realloc(void *ptr, int new_size);

// int	tokens_size(t_token *tokens);
void	print_cmds(t_mini *mini);

//Execution

char	*find_command_path(char *name, char **env);
int		pipex(t_mini *mini, char *exe);
char	**execute(t_mini *mini);


//BuiltIns

int		pwd();
int		cd(char *path);
void	echo(char **argv);
int		env(char **envp, int fd);
void	unset(char **envp, const char *name);
void	export(char **envp, const char *variable);

//extras

int		ft_equal(char *str);
void	ft_error(char *str, char *exe, int status);



#endif