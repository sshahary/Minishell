/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:17:22 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/24 02:12:59 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"


# define FALSE			0
# define TRUE			1

# define ERR			-1
# define SUCCESS 		1

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

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
	int			fds[2];
	int			flag;
	int			preflag;
	t_lst		*list;
	int			redir;
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

// Expander
int		expander(t_mini *mini);
int		check_and_expand(char **s, t_mini *mini);
char	*get_env(const char *name, char **env);
int		handle_quotes(char *str, int *i, char **ex_str);
int		handle_dquotes(char *str, int *i, char **ex_str, t_mini *mini);
int		handle_expansion(char *str, int *i, char **ex_str, t_mini *mini);
void	print_cmds(t_mini *mini);
char	*ft_strnjoin(char *s1, char *s2, int n);

// int	tokens_size(t_token *tokens);
void	print_cmds(t_mini *mini);

#define MAX_PATH_LENGTH 1024

//Execution
void	execute(t_mini *mini);

//Pipex
void	child_process(t_mini *mini);
char	*find_command_path(char *name, char **env);
int		pipex(t_mini *mini);


//BuiltIns

int		pwd();
int		cd(char **cmds, char **env);
void	echo(char **argv);
int		env(char **envp, int fd);
void	unset(char **envp, const char *name);
void	export(char **envp, const char *variable);

//extras

int		ft_equal(char *str);
char	*strjoinslash(const char *s1, const char *s2);
void	ft_pfree(void **str);

//error
void	check_error(char *name, char *str, char *args);
void	ft_exit(char *msg);
void	ft_iderr(char *str1, char *str2);
int		ft_execute_err_1(char *str, char *msg);
int		ft_execute_err_2(char *exe1, char *exe2, char *msg);


#endif