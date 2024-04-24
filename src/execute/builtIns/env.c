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

void	env(char **env)
{
	int		i;
	t_mini	*mini = NULL;

	i = 0;
	while (env[i])
	{
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	mini->exit_code = 0;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	env(envp);
// 	dprintf(2,"test\n");

// 	return (0);
// }
