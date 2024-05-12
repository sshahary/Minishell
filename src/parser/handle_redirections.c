/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_new.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:33:00 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/12 22:13:56 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redirection_helper(t_mini *mini, t_cmds *cmd, int *i);
static void	remove_args(t_cmds *cmd);
static int	handle_redirection_in(t_mini *mini, t_cmds *cmd, int *i);
static int	handle_redirection_out(t_mini *mini, t_cmds *cmd, int *i);
static int	check_file(char *path);
static int	set_fd(char *re, char *path, t_cmds *cmd, t_mini *mini);

void	handle_redirection(t_mini *mini)
{
	t_cmds	*temp;
	int		i;

	temp = mini->cmds;
	while (mini->cmds)
	{
		i = 0;
		while (mini->cmds->args[i])
		{
			if (!handle_redirection_helper(mini, mini->cmds, &i))
			{
				if (!mini->cmds->next)
					return ;
				break;
			}
			i++;
		}
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
}

static int	handle_redirection_helper(t_mini *mini, t_cmds *cmd, int *i)
{
	if (cmd->args[*i][0] == '<' && cmd->args[*i][1] == '\0')
	{
		if (!handle_redirection_in(mini, cmd, i))
		{
			remove_args(cmd);
			return (0);
		}
	}
	else if (cmd->args[*i][0] == '>')
	{
		if (!handle_redirection_out(mini, cmd, i))
		{
			remove_args(cmd);
			return (0);
		}
	}
	return (1);
}

static void	remove_args(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
}

static int	handle_redirection_in(t_mini *mini, t_cmds *cmd, int *i)
{
	if (!cmd->args[*i + 1])
		return (1);
	if (!ft_strcmp(cmd->args[*i], "<") && !check_file(cmd->args[(*i) + 1]))
	{
		mini->exit_code = 1;
		return (0);
	}
	if (!set_fd(cmd->args[*i], cmd->args[(*i) + 1], cmd, mini))
	{
		mini->exit_code = 1;
		return (0);
	}
	remove_element(&cmd->args, *i);
	remove_element(&cmd->args, *i);
	(*i)--;
	return (1);
}

static int	handle_redirection_out(t_mini *mini, t_cmds *cmd, int *i)
{
	if (!cmd->args[*i + 1])
		return (1);
	if (!set_fd(cmd->args[*i], cmd->args[(*i) + 1], cmd, mini))
	{
		mini->exit_code = 1;
		return (0);
	}
	remove_element(&cmd->args, *i);
	remove_element(&cmd->args, *i);
	(*i)--;
	return (1);
}

static int	check_file(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
	}
	return (1);
}

static int	set_fd(char *re, char *path, t_cmds *cmd, t_mini *mini)
{

	if ((!ft_strcmp(re, ">>") || !ft_strcmp(re, ">")) && cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (!ft_strcmp(re, ">"))
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!ft_strcmp(re, ">>"))
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if ((!ft_strcmp(re, "<<") || !ft_strcmp(re, "<")) && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (!ft_strcmp(re, "<"))
		cmd->fd_in = open(path, O_RDONLY);
	if (!ft_strcmp(re, "<<"))
	{
		cmd->fd_in = open("lib/libft/.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		cmd->fd_in = open(path, O_RDONLY);
		heredoc(cmd->fd_in, path, mini);
		close(cmd->fd_in);
		cmd->fd_in = open("lib/libft/.heredoc", O_RDONLY);
	}
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		perror("minishell: ");
		return (0);
	}
	return (1);
}



int	check_if_file_exits(t_mini *mini, char *path)
{
	struct stat	file_stat;
	int fd;

	fd = 0;
	if (stat(path, &file_stat) == 0)
	{
		if (!S_ISDIR(file_stat.st_mode))
		{
			if (access(path, R_OK) == -1)
			{
				mini->exit_code = 126;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(path, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				return (1);
			}
		}
		else
		{
			mini->exit_code = 126;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (1);
		}
	}

	return (0);
}

