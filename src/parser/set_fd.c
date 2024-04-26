/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:49:27 by rpambhar          #+#    #+#             */
/*   Updated: 2024/04/26 14:40:11 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_fd(t_mini *mini)
{
	t_cmds	*temp;
	int		size;

	temp = mini->cmds;
	while (mini->cmds)
	{
		if (mini->cmds->commad == NULL)
		{
			set_fd_and_remove(mini->cmds->args, mini, mini->cmds);
			size = 0;
			while (mini->cmds->args[size])
				size++;
			if (size != 0)
			{
				mini->cmds->commad = ft_strdup(mini->cmds->args[0]);
				removeElementAtIndex(&mini->cmds->args, 0);
			}
			else
				remove_node(&temp, mini->cmds);
		}
		else
			set_fd_and_remove(mini->cmds->args, mini, mini->cmds);
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = temp;
}

void	set_fd_and_remove(char **args, t_mini *mini, t_cmds *cmd)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>')
		{
			if (!strcmp(args[i], "<"))
			{
				if (!check_if_file_exits(args[i + 1]))
				{
					removeElementAtIndex(&cmd->args, i);
					removeElementAtIndex(&cmd->args, i);
					mini->exit_code = 1;
					break ;
				}
			}
			get_and_set_fd(args[i], args[i + 1], cmd);
			removeElementAtIndex(&cmd->args, i);
			removeElementAtIndex(&cmd->args, i);
			i--;
		}
		i++;
	}
}

int	check_if_file_exits(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) != 0)
	{
		if (!S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (0);
		}
	}
	return (1);

}

void get_and_set_fd(char *re, char *path, t_cmds *cmd)
{
	if (!strcmp(re, "<"))
		cmd->fd_in = open(path, O_RDONLY);
	else if (!strcmp(re, ">"))
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (!strcmp(re, ">>"))
		cmd->fd_out = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if ((!strcmp(re, ">>") || !strcmp(re, ">")) && cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	else if ((!strcmp(re, "<<") || !strcmp(re, "<")) && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	else if (!strcmp(re, "<<"))
		; //handle here doc
}

void	removeElementAtIndex(char ***array_ptr, int index)
{
	char	**array;
	int		size;
	int		i;

	i = index;
	array = *array_ptr;
	size = 0;
	while (array[size] != NULL)
		size++;
	free(array[index]);
	while (i < size - 1)
	{
		array[i] = array[i + 1];
		i++;
	}
	array[size - 1] = NULL;
}

void remove_node(t_cmds **head_ref, t_cmds *node_to_remove)
{
	int	i;

	i = 0;
	if (*head_ref == NULL || node_to_remove == NULL)
		return;
	if (*head_ref == node_to_remove)
		*head_ref = node_to_remove->next;
	if (node_to_remove->next != NULL)
		node_to_remove->next->prev = node_to_remove->prev;
	if (node_to_remove->prev != NULL)
		node_to_remove->prev->next = node_to_remove->next;
	free(node_to_remove->commad);
	if (node_to_remove->args != NULL)
	{
		while (node_to_remove->args[i])
		{
			free(node_to_remove->args[i]);
			i++;
		}
		free(node_to_remove->args);
	}
	free(node_to_remove);
}
