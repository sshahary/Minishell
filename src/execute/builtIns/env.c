/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:50:27 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/22 11:22:13 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

int	env(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_equal(envp[i]))
		{
			ft_putstr_fd(envp[i], fd);
			ft_putchar('\n', fd);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int fd = 1;
	while(1)
	{
		env(envp, fd);
	}
dprintf(2,"test\n");

	return (0);
}
