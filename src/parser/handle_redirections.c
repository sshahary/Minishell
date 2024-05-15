/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:33:00 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/13 01:20:11 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redirection_helper(t_mini *mini, t_cmds *cmd, int *i);
static void	remove_args(t_cmds *cmd);
static int	handle_redirection_in(t_mini *mini, t_cmds *cmd, int *i);
static int	handle_redirection_out(t_mini *mini, t_cmds *cmd, int *i);

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
				break ;
			}
			i++;
		}
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
}

static int	handle_redirection_helper(t_mini *mini, t_cmds *cmd, int *i)
{
	if (cmd->args[*i][0] == '<')
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
