/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:18:29 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/01 17:02:11 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc(int fd, char *del, t_mini *mini)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!ft_strcmp(line, del))
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$'))
		{
			check_and_expand(&line, mini, 0);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	remove_element(char ***array_ptr, int index)
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

void	remove_cmd_node(t_mini *mini, t_cmds *node_to_remove)
{
	int	i;

	if (mini == NULL || node_to_remove == NULL)
		return ;
	if (node_to_remove == mini->cmds)
		mini->cmds = node_to_remove->next;
	if (node_to_remove->prev != NULL)
		node_to_remove->prev->next = node_to_remove->next;
	if (node_to_remove->next != NULL)
		node_to_remove->next->prev = node_to_remove->prev;
	if (node_to_remove->fd_in != STDIN_FILENO)
		close(node_to_remove->fd_in);
	if (node_to_remove->fd_out != STDOUT_FILENO)
		close(node_to_remove->fd_out);
	if (node_to_remove->args != NULL)
	{
		i = 0;
		while (node_to_remove->args[i])
		{
			free(node_to_remove->args[i]);
			i++;
		}
		free(node_to_remove->args);
	}
	free(node_to_remove);
}
