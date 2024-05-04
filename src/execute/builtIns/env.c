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

void	env(t_mini *mini, t_cmds *cmds)
{
	int		i;

	i = 1;
	while (cmds->args[i++])
	{
		if (cmds->args[1])
		{
			if (cmds->args[i])
				check_error(cmds->args[0], cmds->args[1], "no such file or directory");
			else
				check_error(cmds->args[0], cmds->args[1], "command not found");
			return ;
		}
	}
	i = 0;
	while (mini->env[i])
	{
		write(STDOUT_FILENO, mini->env[i], ft_strlen(mini->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	mini->exit_code = 0;
}
