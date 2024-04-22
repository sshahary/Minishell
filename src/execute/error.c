/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:26:58 by sshahary          #+#    #+#             */
/*   Updated: 2024/04/22 03:03:21 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(char *str, char *exe, int status)
{
	ft_putstr_fd(exe, 2);
	ft_putstr_fd(":", 2);
	ft_putendl_fd(str, 2);
	return(exit(status));
}


void	check_error(char *name, char *str, char *args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (args[i])
	{
		if (args[i] == '/')
			flag += 1;
		i++;
	}
	if (flag > 0 && !str)
	{
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": no such file or directory", 2);
	}
	else if (!str)
	{
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": command not found", 2);
	}
	return ;
}
