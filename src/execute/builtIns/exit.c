/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 05:39:09 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/05 14:24:36 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	errcode(t_mini *mini)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(mini->exit_code);
}

void	mini_exit(t_mini *mini, t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->args[i] != NULL)
		i++;
	if (i == 1)
		errcode(mini);
	else if (i == 2 && str_is_digit(cmds->args[1]))
		mini->exit_code = ft_atoi(cmds->args[1]);
	else if (i > 2 && str_is_digit(cmds->args[1]))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_execute_err_1("exit", "too many arguments");
		mini->exit_code = 1;
		return ;
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_execute_err_2(": exit", cmds->args[1], "numeric argument required");
		mini->exit_code = 255;
		exit(mini->exit_code & 255);
	}
	errcode(mini);
}
