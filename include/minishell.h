/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:17:22 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/12 22:23:02 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
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
# include <termios.h>
# include "../lib/libft/libft.h"

# define MAX_PATH_LENGTH 1024

extern int	g_sig;

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
t_token	*lexer_handle_redirection_out(t_lexer	*lexer);
t_token	*lexer_handle_word(t_lexer	*lexer);
t_token	*lexer_handle_error(void);
t_token	*lexer_handle_eof(void);
void	free_tokens(t_token *tokens);

// Parser
int		parser(t_mini *mini);
int		check_syntax_errors(t_mini *mini);
int		fill_args_array(int arg_count, t_cmds **cmd, t_token **tokens);
void	free_cmds(t_mini *mini);

// Expander
int		expander(t_mini *mini);
char	*get_env(const char *name, char **env);
int		handle_dquotes(char *str, int *i, char **ex_str, t_mini *mini);
int		handle_expansion(char *str, int *i, char **ex_str, t_mini *mini);
void	print_cmds(t_mini *mini);
char	*ft_strnjoin(char *s1, char *s2, int n);
void	merge_arrays(char ***array1, char **array2, int *i);
int		check_and_expand(char **s, t_mini *mini, int *s_flag);
void	clean_cmds(t_mini *mini);

// Handling Redirections
void	handle_redirection(t_mini *mini);
void	heredoc(int fd, char *del, t_mini *mini);
void	remove_element(char ***array_ptr, int index);
void	remove_cmd_node(t_mini *mini, t_cmds *node_to_remove);
void	print_cmds(t_mini *mini);
int	check_if_file_exits(t_mini *mini, char *path);

// Signals
void	signal_handler(void);
void	configure_terminal(void);

//Execution
void	executor(t_mini *mini);
int		builtin_check_and_run(t_mini *mini, t_cmds *cmd);
int		count_cmds(t_cmds *cmds);
char	*find_path(t_mini *mini, char *cmd);

//Handler
void	handle_single_cmd(t_mini *mini);
void	handle_multiple_cmds(t_mini *mini);
int		initialize_fds(int ***fds, int n_cmds);
// void	fork_process(t_mini *mini, int n_cmds, int **fds);
void	fork_process(t_mini *mini, int n_cmds, int **fds);

void	fork_child_proccess(t_mini *mini, t_cmds *cmds, int i, int **fds);
void	execute_pipe_cmd(t_mini *mini, int i, t_cmds *cmd, int **fd);
void	setup_child_process(t_mini *mini, t_cmds *cmds, int fd_1, int fd_2);
void	close_fds(int **fds, int n_cmds);
void	wait_pids(t_mini *mini, int n_cmds);

//BuiltIns
void	echo(t_cmds *cmds, t_mini *mini);
void	pwd(t_mini *mini);
void	cd(t_mini *mini, t_cmds *cmds);
void	env(t_mini *mini, t_cmds *cmds);
void	export(t_mini *mini, t_cmds *cmds);
void	printexport(char **env);
void	unset(t_mini *mini, t_cmds *cmds);
void	mini_exit(t_mini *mini, t_cmds *cmds);
int		isvalidenv(char *name);

//Extras
int		ft_dstrlen(char **str);
int		remove_char(char *str, char c);
int		checkexport(char *path, char ***env);
char	*ft_strtok(char *str, char sep);
int		str_is_digit(char *str);

//Errors
void	check_error(char *name, char *str, char *msg);
void	ft_exit(char *msg);
int		ft_iderr(char *str1, char *str2, int exitcode);
int		ft_execute_err_1(char *str, char *msg);
int		ft_execute_err_2(char *exe1, char *exe2, char *msg);
int		path_err(char *exe1, char *exe2, char *msg);

#endif