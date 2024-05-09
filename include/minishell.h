/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:17:22 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/09 01:59:32 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
#include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
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
	t_type			type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmds
{
	char			**args;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	int				fd_in;
	int				fd_out;
	int				success_flag;
}	t_cmds;

typedef struct s_mini
{
	char		*input;
	t_token		*tokens;
	char		**env;
	t_cmds		*cmds;
	int			exit_code;
	pid_t		*pids;
	int			fds[2];
}	t_mini;

typedef struct s_lexer
{
	char	*input;
	int		position;
	int		dquote;
	int		squote;
}	t_lexer;

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
int		check_and_expand(char **s, t_mini *mini, int *s_flag);
char	*get_env(const char *name, char **env);
int		handle_quotes(char *str, int *i, char **ex_str);
int		handle_dquotes(char *str, int *i, char **ex_str, t_mini *mini);
int		handle_expansion(char *str, int *i, char **ex_str, t_mini *mini);
int		handle_pid_exitcode_expansion(char *str, int *i, char **ex_str, t_mini *m);
void	print_cmds(t_mini *mini);
char	*ft_strnjoin(char *s1, char *s2, int n);
void	merge_arrays(char ***array1, char **array2, int *i);
int		expand_and_join(char *str, int *i, char **ex_str, t_mini *mini);

// Handling Redirections
void	handle_redirection(t_mini *mini);
void	heredoc(int fd, char *del, t_mini *mini);
void	remove_element(char ***array_ptr, int index);
void	remove_cmd_node(t_mini *mini, t_cmds *node_to_remove);


// My executor
void	executor(t_mini *mini);
void	handle_single_cmd(t_mini *mini);
void	handle_multiple_cmds(t_mini *mini);
void	fork_process(t_mini *mini, int n_cmds, int **fds);
void	execute_pipe_cmd(t_mini *mini, int i, t_cmds *cmd, int **fd);
// void	execute_pipe_cmd(t_mini *mini, int i, t_cmds *cmd, int *fd);
void	close_fds(int **fds, int n_cmds);
void	wait_pids(t_mini *mini, int n_cmds);
int		initialize_fds(int ***fds, int n_cmds);
char	*find_path(t_mini *mini, char *cmd);
int		count_cmds(t_cmds *cmds);
int		builtin_check_and_run(t_mini *mini, t_cmds *cmd);





// int	tokens_size(t_token *tokens);
void	print_cmds(t_mini *mini);

#define MAX_PATH_LENGTH 1024

//Execution
void	execute(t_mini *mini);
// char	**execute(t_mini *mini);
int		check_builtin(char **args);
int	builtin(t_mini	*mini, t_cmds *cmds);

//Pipex
int		parent_process(t_mini *mini, pid_t pid);
// void	child_process(t_mini *mini);
void	child_process(t_cmds *cmd, t_mini *mini);
char		*find_command_path(char *cmdline, char **envs);
// char	*find_command_path(char *name, char **env);
// int		pipex(t_mini *mini);
// int	pipex(t_mini *mini);
int		pipex(t_cmds *cmd, t_mini *mini);


//BuiltIns

void	pwd(t_mini *mini);
// void	cd(t_mini *mini);
void	cd(t_mini *mini, t_cmds *cmds);
// void	echo(char **argv);
void	echo(t_cmds *cmds, t_mini *mini);
// void	echo(t_mini *mini, t_cmds *cmds);
void	env(t_mini *mini, t_cmds *cmds);
// void	export(t_mini *mini);
void	export(t_mini *mini, t_cmds *cmds);
// void	unset(t_mini *mini);
void	unset(t_mini *mini, t_cmds *cmds);
// void	mini_exit(t_mini *mini);
void	mini_exit(t_mini *mini, t_cmds *cmds);
int	isvalidenv(char *name);

//Extras

char	*strjoinslash(const char *s1, const char *s2);
int		ft_dstrlen(char **str);
void	ft_pfree(void **str);
int		remove_char(char *str, char c);
int		checkexport(char *path, char ***env);
char	*ft_strtok(char *str, char sep);
int		str_is_digit(char *str);
int		isvalidnum(char *str);
char	*get_path_value(char *name, char **env);

//Errors
void	check_error(char *name, char *str, char *msg);
void	ft_exit(char *msg);
int		ft_iderr(char *str1, char *str2);
int		ft_execute_err_1(char *str, char *msg);
int		ft_execute_err_2(char *exe1, char *exe2, char *msg);

void execute_redirection(int fd_in, int fd_out);


#endif