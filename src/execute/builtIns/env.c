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

// void	env(char **env)
void	env(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env[i])
	{
		write(STDOUT_FILENO, mini->env[i], ft_strlen(mini->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	mini->exit_code = 0;
}

// int		main(void)
// {
// 	t_mini	mini;
// 	char	*envp[] = {"USER=sshahavhgdbbbbbry", "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library", "TERM=xterm-256color", NULL};

// 	mini.env = envp;
// 	env(&mini);
// 	return (0);
// }
