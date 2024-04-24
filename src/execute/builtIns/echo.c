
 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:55 by sshahary          #+#    #+#             */
/*   Updated: 2024/03/22 11:35:22 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


void		exit_code(void)
{
	t_mini	*mini;

	ft_putstr_fd(ft_itoa(mini->exit_code), 1);
}

void		echoenv(char **cmds, char **envs, int i)
{
	char	*value;
	if (cmds[1][0] == '$' && cmds[1][1] == '?')
		print_exit_status();
	value = find_command_path(&(cmds[i][1]), envs);
	ft_putstr_fd(value, STDIN_FILENO);
}

static	int		args_n(char **args)
{
	int	i;

	if (ft_strncmp(args, "-n", 2) != 0)
		return (0);
	i = 2;
	while (args[i])
	{
		if (args[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **args, char **env)
{
	int	i;
	int	res;

	i = 1;
	res = 0;
	while (args_n(args[i]))
	{
		res = -1;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] == '\'')
			res = remove_char(args[i], '\'');
		if (args[i][0] == '$' && res != 1)
			echoenvv(args, env, i);
		else
			ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (res != -1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
